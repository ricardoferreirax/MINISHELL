/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/22 09:04:28 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"
#include "errno.h"

static void	execute_external_cmd(t_subcmd *subcmd, t_mini *mini)
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
    pid_t pid;
    int   status;

    if (!subcmd || !mini || !subcmd->args || !subcmd->args[0])
        return (0);  // CMD_EMPTY
    pid = fork();
    if (pid < 0)
    {
        error_exit("minishell: fork failed");
        return (1);
    }
    if (pid == 0)
    {
        execute_subcmd_with_redirs(subcmd, mini);
        exit(1);
    }
    status = wait_for_children(pid);
	return (status);
}

void	execute_subcmd_with_redirs(t_subcmd *subcmd, t_mini *mini)
{
	if (!subcmd || !mini || !subcmd->args || !subcmd->args[0])
        _exit(0);
	handle_redirs(subcmd);
	if (subcmd->cmd_type == BUILTIN_CMD)
	{
		execute_builtin(subcmd, mini);
		exit(0);
	}
	else if (subcmd->cmd_type == ABS_PATH_CMD
		|| subcmd->cmd_type == REL_PATH_CMD
		|| subcmd->cmd_type == SIMPLE_CMD)
	{
		execute_external_cmd(subcmd, mini);
		exit(1);
	}
	exit(0);
}