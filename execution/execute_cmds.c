/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 22:41:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"
#include "errno.h"

void	execute_external_cmd(t_subcmd *subcmd, t_mini *mini)
{
	char	*cmd_path;

	cmd_path = handle_cmd_path(subcmd->args[0], mini->env);
	if (!cmd_path)
	{
		cmd_not_found_msg(subcmd->args[0]);
		exit(127);
	}
	execve(cmd_path, subcmd->args, mini->env);
	perror("execve failed");
	free(cmd_path);
	if (errno == EACCES)
		exit(126);
	else if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

int execute_single_cmd(t_subcmd *subcmd, t_mini *mini)
{
    int orig_stdin;
    int orig_stdout;

    orig_stdin = dup(STDIN_FILENO);
    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdin == -1 || orig_stdout == -1)
        return (perror("MiNyanshell: dup original fds"), 1);
    if (handle_redirs_in_child(subcmd) != 0)
    {
        reset_fds(orig_stdin, orig_stdout);
        close_heredoc(subcmd);
        return (1);
    }
    if (!(subcmd->args && subcmd->args[0] && is_builtin(subcmd->args[0])))
    {
        reset_fds(orig_stdin, orig_stdout);
        close_heredoc(subcmd);
        return (-1);
    }
    execute_builtin(subcmd, mini);
    reset_fds(orig_stdin, orig_stdout);
    close_heredoc(subcmd);
    return (0);
}
