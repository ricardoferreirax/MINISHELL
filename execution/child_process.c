/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:16:03 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/18 12:29:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"
#include "../include/execution.h"
#include "../include/signals.h"

static void	execute_child_cmd(t_cmd *cmd, t_mini *mini)
{
	int		status;
	char	**envyan_array;

	if (!cmd)
		minyanshell_cleanup_and_exit(mini, 0);
	if (apply_redirs_in_child(cmd) != 0)
		minyanshell_cleanup_and_exit(mini, 1);
	if (!cmd->args || !cmd->args[0])
		minyanshell_cleanup_and_exit(mini, 0);
	if (cmd->args[0][0] == '\0')
	{
		cmd_not_found_msg(cmd->args[0]);
		minyanshell_cleanup_and_exit(mini, 127);
	}
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, mini);
		minyanshell_cleanup_and_exit(mini, status);
	}
	envyan_array = envyan_to_array(mini->envyan);
	if (!envyan_array)
		minyanshell_cleanup_and_exit(mini, 1);
	execute_external_in_child(cmd, envyan_array, mini);
}

static void	first_child(t_cmd *cmd, t_pipeline *pp)
{
	prepare_first(cmd, pp);
	if (pp->need_next_stdout && cmd->next)
	{
		if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
			error_exit("MiNyanShell: dup2 failed (pipe write)");
		close_fd_safe(&pp->pipefd[0]);
	}
	execute_child_cmd(cmd, pp->mini);
}

static void	middle_child(t_cmd *cmd, t_pipeline *pp)
{
	prepare_middle(cmd, pp);
	if (pp->need_prev_stdin)
	{
		if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
			error_exit("MiNyanShell: dup2 failed (pipe read)");
	}
	if (pp->need_next_stdout && cmd->next)
	{
		if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
			error_exit("MiNyanShell: dup2 failed (pipe write)");
		close_fd_safe(&pp->pipefd[0]);
	}
	execute_child_cmd(cmd, pp->mini);
}

static void	last_child(t_cmd *cmd, t_pipeline *pp)
{
	prepare_last(cmd, pp);
	if (pp->need_prev_stdin)
	{
		if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
			error_exit("MiNyanShell: dup2 failed (pipe read)");
	}
	execute_child_cmd(cmd, pp->mini);
}

void	child_execute_cmd(t_cmd *cmd, t_pipeline *pp)
{
	minyanshell_signals(CHILD_EXEC);
	if (pp->prev_pipefd == -1)
		first_child(cmd, pp);
	else if (!cmd->next)
		last_child(cmd, pp);
	else
		middle_child(cmd, pp);
}
