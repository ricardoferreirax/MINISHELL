/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 09:48:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

static void run_subcmd_child(t_subcmd *sub, t_mini *mini)
{
    if (apply_redirs_in_child(sub) != 0)
        exit(1);
    if (!sub->args || !sub->args[0])
        exit(0);
    if (sub->args[0][0] == '\0') 
    {
        cmd_not_found_msg(sub->args[0]);
        exit(127);
    }
    if (is_builtin(sub->args[0]))  // Na pipeline, os builtins executam no child
    {
        execute_builtin(sub, mini);
        exit(mini->last_status);
    }
    execute_external_cmd(sub, mini);
}

static void first_child(t_cmd *cmd, t_pipeline *pp)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (cmd->next) 
    {
        if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("MiNyanShell: dup2 failed (pipe write)");
        close(pp->pipefd[0]);
    }
    run_subcmd_child(subcmd, pp->mini);
}

static void middle_child(t_cmd *cmd, t_pipeline *pp)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
        error_exit("MiNyanShell :3 : dup2 failed (pipe read)");
    if (cmd->next) 
    {
        if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
        close(pp->pipefd[0]);
    }
    run_subcmd_child(subcmd, pp->mini);
}

static void last_child(t_cmd *cmd, t_pipeline *pp)
{
    t_subcmd *sub;

    sub = cmd->head;
    if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
        error_exit("MiNyanShell: dup2 failed (pipe read)");
    run_subcmd_child(sub, pp->mini);
}

void child_execute_cmd(t_cmd *cmd, t_pipeline *pp)
{
    // set_child_signals();  // SIGINT/SIGQUIT default no filho
    if (pp->prev_pipefd == -1) // não há pipe anterior - é o primeiro comando
        first_child(cmd, pp);
    else if (!cmd->next) 
        last_child(cmd, pp);  // não há próximo - último comando
    else
        middle_child(cmd, pp);  // tem pipe anterior e também há próximo
}













// static void first_child(t_cmd *cmd, t_pipeline *pp)
// {
//     t_subcmd *subcmd;

//     subcmd = cmd->head;
//     if (cmd->next)
//     {
//         if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
//             error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
//         close(pp->pipefd[0]);
//     }
//     execute_subcommand(subcmd, pp->mini);
// }

// static void middle_child(t_cmd *cmd, t_pipeline *pp)
// {
//     t_subcmd *subcmd;

//     subcmd = cmd->head;
//     if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
//         error_exit("MiNyanShell :3 : dup2 failed (pipe read)");
//     if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
//         error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
//     close(pp->pipefd[0]);
//     execute_subcommand(subcmd, pp->mini);
// }

// static void last_child(t_cmd *cmd, t_pipeline *pp)
// {
//     t_subcmd *subcmd;

//     subcmd = cmd->head;
//     if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
//         error_exit("MiNyanShell :3 : dup2 failed (pipe read)");

//     execute_subcommand(subcmd, pp->mini);
// }

// void child_process(t_cmd *cmd, t_pipeline *pp)
// {
//     if (pp->prev_pipefd == -1 && cmd == pp->mini->head)
//         first_child(cmd, pp);
//     else if (cmd->next)
//         middle_child(cmd, pp);
//     else if (!cmd->next)
//         last_child(cmd, pp);
// }