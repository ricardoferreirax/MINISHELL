/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:47:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"
#include "parsing.h"
#include <string.h>

static int	heredoc_read_loop(t_redir *redir, t_mini *mini, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (isatty(STDIN_FILENO) == 0)
				return (130);
			warn_heredoc_eof(redir->delimiter);
			return (0);
		}
		if (redir->delimiter && ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (expand_heredoc_line(&line, redir, mini) != 0)
			return (-1);
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	return (0);
}

static void	child_heredoc(t_redir *redir, t_mini *mini, int pipefd[2],
		t_cmd *cmd)
{
	int	exit_code;

	close_fd_safe(&pipefd[0]);
	setup_heredoc_signals();
	exit_code = heredoc_read_loop(redir, mini, pipefd[1]);
	close_fd_safe(&pipefd[1]);
	if (cmd->in_fd != -1)
		close_fd_safe(&cmd->in_fd);
	minyanshell_cleanup_and_exit(mini, exit_code);
}

static int	parent_heredoc_control(t_cmd *cmd, t_mini *mini, int pipefd[2],
		pid_t pid)
{
	int	exit_code;

	close_fd_safe(&pipefd[1]);
	exit_code = wait_for_single(pid);
	if (exit_code == 130)
	{
		mini->last_status = 130;
		close_fd_safe(&pipefd[0]);
		return (130);
	}
	if (exit_code != 0)
	{
		close_fd_safe(&pipefd[0]);
		return (1);
	}
	if (cmd->in_fd != -1)
		close_fd_safe(&cmd->in_fd);
	cmd->in_fd = pipefd[0];
	return (0);
}

static int	handle_single_heredoc(t_cmd *cmd, t_redir *redir, t_mini *mini)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("MiNyanShell: pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		close_fd_safe(&pipefd[0]);
		close_fd_safe(&pipefd[1]);
		return (perror("MiNyanShell: fork"), 1);
	}
	if (pid == 0)
		child_heredoc(redir, mini, pipefd, cmd);
	else
		return (parent_heredoc_control(cmd, mini, pipefd, pid));
	return (0);
}

int	process_all_heredocs(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (handle_single_heredoc(cmd, redir, mini) != 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
