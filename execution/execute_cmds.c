/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 02:16:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "errno.h"

void execute_external_cmd(t_cmd *cmd, char **envyan_array)
{
    char *cmd_path;

    if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0])
        exit(0);
    cmd_path = handle_cmd_path(cmd->cmd_args[0], envyan_array);
    if (!cmd_path)
    {
        free_str_array(envyan_array);
        cmd_not_found_msg(cmd->cmd_args[0]);
        exit(127);
    }
    execve(cmd_path, cmd->cmd_args, envyan_array);
    perror("execve failed");
    free(cmd_path);
    free_str_array(envyan_array);
    if (errno == EACCES || errno == EISDIR)
        exit(126);
    else if (errno == ENOENT)
        exit(127);
    exit(EXIT_FAILURE);
}

int run_external_single(t_cmd *cmd, t_mini *mini)
{
    pid_t pid;
    int   status;
	char **envyan_array;

    pid = fork();
    if (pid == -1)
        return (perror("MiNyanShell: fork failed"), 1);
    if (pid == 0)
    {
        // set_child_signals();
        if (apply_redirs_in_child(cmd) != 0)
            exit(1);
        if (!cmd->cmd_args || !cmd->cmd_args[0])
            exit(0);
        if (cmd->cmd_args[0][0] == '\0')
        {
            cmd_not_found_msg(cmd->cmd_args[0]);
            exit(127);
        }
		envyan_array = envyan_to_array(mini->envyan);
		if (!envyan_array)
			exit(1);
        execute_external_cmd(cmd, envyan_array);
    }
    close_heredoc(cmd);
    status = wait_for_single(pid);
	mini->last_status = status;
    return (status);
}

int run_redirs_without_cmd(t_cmd *cmd, t_mini *mini)
{
    int orig_stdin;
    int orig_stdout;
    int result;

    if (!cmd)
        return (0);
    orig_stdin  = dup(STDIN_FILENO);
    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdin == -1 || orig_stdout == -1)
        return (perror("MiNyanShell: dup original fds"), 1);
    result = apply_redirs_in_child(cmd);
    reset_fds(orig_stdin, orig_stdout);
    close_heredoc(cmd);
    if (mini)
        mini->last_status = result;
    return (result);
}

int execute_single_cmd(t_cmd *cmd, t_mini *mini)
{
    int orig_stdin;
    int orig_stdout;
    int status;

    while (cmd && cmd->next)            // avança até ao primeiro nó com args válidos (ignora nós vazios no início)
    {
        if (cmd->cmd_args && cmd->cmd_args[0])
            break;
        cmd = cmd->next;
    }
    if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !is_builtin(cmd->cmd_args[0]))  // se não há comando ou não é builtin, devolve -1 para tratarmos como externo
        return (-1);
    orig_stdin  = dup(STDIN_FILENO);
    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdin == -1 || orig_stdout == -1)
        return (perror("MiNyanShell: dup original fds"), 1);
    if (apply_redirs_in_child(cmd) != 0)
    {
        reset_fds(orig_stdin, orig_stdout);
        close_heredoc(cmd);
    	mini->last_status = 1;
        return (1);
    }
    status = execute_builtin(cmd, mini);
    reset_fds(orig_stdin, orig_stdout);
    close_heredoc(cmd);
    mini->last_status = status;
    return (0);
}
