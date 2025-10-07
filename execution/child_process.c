/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 17:44:12 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

static void execute_child_cmd(t_cmd *cmd, t_mini *mini)
{
    int status;
    char **envyan_array;

    if (apply_redirs_in_child(cmd) != 0)
        exit(1);
    if (!cmd->cmd_args || !cmd->cmd_args[0])
        exit(0);
    if (cmd->cmd_args[0][0] == '\0')
    {
        cmd_not_found_msg(cmd->cmd_args[0]);
        exit(127);
    }
    if (is_builtin(cmd->cmd_args[0]))
    {
        status = execute_builtin(cmd, mini);
        exit(status);
    }
    envyan_array = envyan_to_array(mini->envyan);
    if (!envyan_array)
        exit(1);
    execute_external_in_child(cmd, envyan_array);
}

static void first_child(t_cmd *cmd, t_pipeline *pp)
{
    if (cmd->next)
    {
        if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("MiNyanShell: dup2 failed (pipe write)");
        close_fd_safe(&pp->pipefd[0]);
    }
    execute_child_cmd(cmd, pp->mini);
}

static void middle_child(t_cmd *cmd, t_pipeline *pp)
{
    if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
        error_exit("MiNyanShell: dup2 failed (pipe read)");
    if (cmd->next)
    {
        if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("MiNyanShell: dup2 failed (pipe write)");
        close_fd_safe(&pp->pipefd[0]);
    }
    execute_child_cmd(cmd, pp->mini);
}

static void last_child(t_cmd *cmd, t_pipeline *pp)
{
    if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
        error_exit("MiNyanShell: dup2 failed (pipe read)");
    execute_child_cmd(cmd, pp->mini);
}

void child_execute_cmd(t_cmd *cmd, t_pipeline *pp)
{
    // set_child_signals();  // SIGINT/SIGQUIT default no child
    if (pp->prev_pipefd == -1) // não há pipe anterior - é o primeiro comando
        first_child(cmd, pp);
    else if (!cmd->next) 
        last_child(cmd, pp);  // não há próximo - último comando
    else
        middle_child(cmd, pp);  // tem pipe anterior e também há próximo
}
