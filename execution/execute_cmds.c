/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/24 23:51:11 by rmedeiro         ###   ########.fr       */
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

void	execute_subcommand(t_subcmd *subcmd, t_mini *mini)
{
    int status;
    
	if (!subcmd || !mini || !subcmd->args || !subcmd->args[0])
        exit(0);
	handle_redirs(subcmd);
	if (subcmd->cmd_type == BUILTIN_CMD)
	{
        status = execute_builtin(subcmd, mini);
		exit(status);
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

static int run_external_fork(t_subcmd *subcmd, t_mini *mini, int stdin_backup, int stdout_backup)
{
    pid_t pid;
    int   status;

    pid = fork();
    if (pid == -1)
    {
        perror("MiNyanShell :3 : fork failed");
        return (1);
    }
    if (pid == 0) // CHILD
    {
        if (!handle_redirs(subcmd))
            exit(1);
        execute_external_cmd(subcmd, mini); // só retorna em caso de erro
        exit(1);
    }
    waitpid(pid, &status, 0);
    safe_dup2_and_close(stdout_backup, STDOUT_FILENO);
    safe_dup2_and_close(stdin_backup, STDIN_FILENO);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

static int backup_stdio(int *stdin_backup, int *stdout_backup)
{
    *stdin_backup = dup(STDIN_FILENO);
    *stdout_backup = dup(STDOUT_FILENO);
    if (*stdin_backup == -1 || *stdout_backup == -1)
    {
        perror("minishell: dup error");
        if (*stdin_backup != -1)
            close(*stdin_backup);
        if (*stdout_backup != -1)
            close(*stdout_backup);
        return (1);
    }
    return (0);
}

int execute_single_cmd(t_subcmd *subcmd, t_mini *mini)
{
    int stdin_backup;
    int stdout_backup;

    if (!subcmd || !mini)
        return (0);
    if (backup_stdio(&stdin_backup, &stdout_backup))
        return (1);

    if (subcmd->cmd_type == BUILTIN_CMD && builtin_runs_in_parent(subcmd))
    {
        if (!handle_redirs(subcmd))
        {
            safe_dup2_and_close(stdout_backup, STDOUT_FILENO);
            safe_dup2_and_close(stdin_backup, STDIN_FILENO);
            return (1);
        }
        return execute_parent_builtin_with_redirs(subcmd, mini);
    }
    return (run_external_fork(subcmd, mini, stdin_backup, stdout_backup));
}
