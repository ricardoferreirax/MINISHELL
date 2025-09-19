/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 22:15:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static void last_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (safe_dup2_and_close(ctx->prev_fd, STDIN_FILENO) != 0)
        error_exit("dup2 failed (pipe read)");
    if (subcmd->out_fd != -1)
        if (safe_dup2_and_close(subcmd->out_fd, STDOUT_FILENO) != 0)
            error_exit("dup2 failed (outfile)");
    exec_subcmd(subcmd, ctx->mini->env);
    exit(1);
}

static void middle_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
     if (safe_dup2_and_close(ctx->prev_fd, STDIN_FILENO) != 0)
        error_exit("dup2 failed (pipe read)");

    if (cmd->next)
        if (safe_dup2_and_close(ctx->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("dup2 failed (pipe write)");

    close(ctx->pipefd[0]);
    exec_subcmd(subcmd, ctx->mini->env);
    exit(1); 
}

static void first_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    if (cmd->next)
        if (safe_dup2_and_close(ctx->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("dup2 failed (pipe write)");
    if (subcmd->in_fd != -1)
        if (safe_dup2_and_close(subcmd->in_fd, STDIN_FILENO) != 0)
            error_exit("dup2 failed (stdin)");
    close(ctx->pipefd[0]);
    exec_subcmd(subcmd, ctx->mini->env);
    exit(1); // se o execve falhar
}

void child_process(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (ctx->prev_fd == -1 && cmd == ctx->mini->head) // se é o first command
        first_child(cmd, ctx);
    else if (cmd->next)  // se for um middle command
        middle_child(cmd, ctx);
    else if (!cmd->next) // se for o last command
        last_child(cmd, ctx);
}
