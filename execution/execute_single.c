/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:23:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:31:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"

static int	has_redirs(const t_cmd *cmd)
{
	return (cmd && cmd->redirs != NULL);
}

static int	exec_builtin_no_redirs(t_cmd *cmd, t_mini *mini)
{
	int	status;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		close_heredoc(cmd);
		mini->last_status = 0;
		return (0);
	}
	status = execute_builtin(cmd, mini);
	close_heredoc(cmd);
	mini->last_status = status;
	return (status);
}

static int	exec_builtin_with_redirs(t_cmd *cmd, t_mini *mini)
{
	int	orig_stdin;
	int	orig_stdout;
	int	status;

	minyanshell_signals(PARENT_WAIT);
	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (orig_stdin == -1 || orig_stdout == -1)
		return (minyanshell_signals(PROMPT), perror("MiNyan: dup error"), 1);
	if (apply_redirs_in_child(cmd) != 0)
	{
		reset_fds(orig_stdin, orig_stdout);
		close_heredoc(cmd);
		minyanshell_signals(PROMPT);
		mini->last_status = 1;
		return (1);
	}
	status = execute_builtin(cmd, mini);
	reset_fds(orig_stdin, orig_stdout);
	close_heredoc(cmd);
	minyanshell_signals(PROMPT);
	mini->last_status = status;
	return (status);
}

int	execute_single_cmd(t_cmd *cmd, t_mini *mini)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		close_heredoc(cmd);
		mini->last_status = 0;
		return (0);
	}
	if (!is_builtin(cmd->args[0]))
		return (NOT_BUILTIN);
	if (!has_redirs(cmd))
		return (exec_builtin_no_redirs(cmd, mini));
	return (exec_builtin_with_redirs(cmd, mini));
}
