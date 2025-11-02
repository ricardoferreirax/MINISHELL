/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/02 12:20:07 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/envyan.h"
#include "../include/signals.h"

void execute_external_in_child(t_cmd *cmd, char **envyan_array, t_mini *mini)
{
    char *cmd_path;

    if (!cmd || !cmd->args || !cmd->args[0])
        minyanshell_child_cleanup_and_exit(mini, 0);
    cmd_path = handle_cmd_path(cmd->args[0], envyan_array);
    if (!cmd_path)
    {
        free_str_array(envyan_array);
        cmd_not_found_msg(cmd->args[0]);
        minyanshell_child_cleanup_and_exit(mini, 127);
    }
    execve(cmd_path, cmd->args, envyan_array);
    perror("execve failed");
    free(cmd_path);
    free_str_array(envyan_array);
    if (errno == EACCES || errno == EISDIR)
        minyanshell_child_cleanup_and_exit(mini, 126);
    else if (errno == ENOENT)
        minyanshell_child_cleanup_and_exit(mini, 127);
    minyanshell_child_cleanup_and_exit(mini, EXIT_FAILURE);
}

static void setup_and_exec_child_external(t_cmd *cmd, t_mini *mini)
{
    char **envvyan;

    minyanshell_signals(CHILD_EXEC);
    if (apply_redirs_in_child(cmd) != 0)
        minyanshell_child_cleanup_and_exit(mini, 1);
    if (!cmd->args || !cmd->args[0])
        minyanshell_child_cleanup_and_exit(mini, 0);
    if (cmd->args[0][0] == '\0')
    {
        cmd_not_found_msg(cmd->args[0]);
        minyanshell_child_cleanup_and_exit(mini, 127);
    }
    envvyan = envyan_to_array(mini->envyan);
    if (!envvyan)
        minyanshell_child_cleanup_and_exit(mini, 1);
    execute_external_in_child(cmd, envvyan, mini);
}

int execute_external_cmd(t_cmd *cmd, t_mini *mini)
{
    pid_t pid;
    int   status;

    minyanshell_signals(PARENT_WAIT);
    pid = fork();
    if (pid == -1)
    {
        minyanshell_signals(PROMPT);
        return (perror("MiNyanShell: fork failed"), 1);
    }
    if (pid == 0)
    {
        minyanshell_signals(CHILD_EXEC);
        setup_and_exec_child_external(cmd, mini);
    }
    close_heredoc(cmd);
    status = wait_for_single(pid);
    minyanshell_signals(PROMPT);
    mini->last_status = status;
    return (status);
}
