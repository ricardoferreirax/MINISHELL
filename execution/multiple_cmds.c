/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:57:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:47:30 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int	extract_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static void	wait_for_children(t_mini *mini, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
		{
			if (errno != EINTR)
				break ;
		}
		else if (pid == last_pid)
		{
			mini->last_status = extract_exit_code(status);
		}
	}
}

static void	parent_pipe_control(t_cmd *cmd, t_pipeline *pp)
{
	close_fd_safe(&pp->prev_pipefd);
	if (cmd->next)
	{
		close_fd_safe(&pp->pipefd[1]);
		pp->prev_pipefd = pp->pipefd[0];
	}
	else
	{
		pp->prev_pipefd = -1;
		close_fd_safe(&pp->pipefd[0]);
		close_fd_safe(&pp->pipefd[1]);
	}
	close_heredoc(cmd);
}

static int	create_pipe_and_fork(t_cmd *cmd, t_pipeline *pp)
{
	pp->pipefd[0] = -1;
	pp->pipefd[1] = -1;
	if (cmd->next)
	{
		if (pipe(pp->pipefd) == -1)
		{
			perror("MiNyanshell: error creating pipe");
			if (pp->prev_pipefd != -1)
			{
				close(pp->prev_pipefd);
				pp->prev_pipefd = -1;
			}
			return (-1);
		}
	}
	if (safe_fork(cmd, pp) != 0)
		return (-1);
	return (0);
}

int	execute_multiple_cmds(t_cmd *cmds, t_mini *mini)
{
	t_pipeline	pp;
	t_cmd		*current_cmd;

	pp.pid = -1;
	pp.pipefd[0] = -1;
	pp.pipefd[1] = -1;
	pp.prev_pipefd = -1;
	pp.last_status = 0;
	pp.mini = mini;
	current_cmd = cmds;
	while (current_cmd)
	{
		if (create_pipe_and_fork(current_cmd, &pp) == -1)
			return (handle_fork_error(current_cmd, &pp), 1);
		if (pp.pid == 0)
			child_execute_cmd(current_cmd, &pp);
		else
			parent_pipe_control(current_cmd, &pp);
		current_cmd = current_cmd->next;
	}
	wait_for_children(mini, pp.pid);
	return (mini->last_status);
}
