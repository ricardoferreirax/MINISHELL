/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/08 16:50:18 by pfreire-         ###   ########.fr       */
=======
/*   Updated: 2025/10/15 13:58:12 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/envyan.h"

<<<<<<< HEAD
void execute_external_in_child(t_cmd *cmd, char **envyan_array)
=======
void execute_external_in_child(t_cmd *cmd, char **envyan_array, t_mini *mini)
>>>>>>> ricardo
{
    char *cmd_path;

    if (!cmd || !cmd->args || !cmd->args[0])
<<<<<<< HEAD
        exit(0);
=======
        minyanshell_child_cleanup_and_exit(mini, 0);
>>>>>>> ricardo
    cmd_path = handle_cmd_path(cmd->args[0], envyan_array);
    if (!cmd_path)
    {
        free_str_array(envyan_array);
        cmd_not_found_msg(cmd->args[0]);
<<<<<<< HEAD
        exit(127);
=======
        minyanshell_child_cleanup_and_exit(mini, 127);
>>>>>>> ricardo
    }
    execve(cmd_path, cmd->args, envyan_array);
    perror("execve failed");
    free(cmd_path);
    free_str_array(envyan_array);
    if (errno == EACCES || errno == EISDIR)
<<<<<<< HEAD
        exit(126);
    else if (errno == ENOENT)
        exit(127);
    exit(EXIT_FAILURE);
=======
        minyanshell_child_cleanup_and_exit(mini, 126);
    else if (errno == ENOENT)
        minyanshell_child_cleanup_and_exit(mini, 127);
    minyanshell_child_cleanup_and_exit(mini, EXIT_FAILURE);
>>>>>>> ricardo
}

static void setup_and_exec_child_external(t_cmd *cmd, t_mini *mini)
{
    char **envvyan;
<<<<<<< HEAD

    // set_child_signals();
    if (apply_redirs_in_child(cmd) != 0)
        exit(1);
    if (!cmd->args || !cmd->args[0])
        exit(0);
    if (cmd->args[0][0] == '\0') {
        cmd_not_found_msg(cmd->args[0]);
        exit(127);
    }
    envvyan = envyan_to_array(mini->envyan);
    if (!envvyan)
        exit(1);
    execute_external_in_child(cmd, envvyan);
=======
	
    // set_child_signals();
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
>>>>>>> ricardo
}

int execute_external_cmd(t_cmd *cmd, t_mini *mini)
{
    pid_t pid;
    int   status;

    pid = fork();
    if (pid == -1)
        return (perror("MiNyanShell: fork failed"), 1);
    if (pid == 0)
        setup_and_exec_child_external(cmd, mini);
    close_heredoc(cmd);
    status = wait_for_single(pid);
	mini->last_status = status;
    return (status);
}
<<<<<<< HEAD

=======
>>>>>>> ricardo
