/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/22 09:03:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

static void last_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (safe_dup2_and_close(ctx->prev_fd, STDIN_FILENO) != 0)
        error_exit("dup2 failed (pipe read)");
    execute_subcmd_with_redirs(subcmd, ctx->mini);
    exit(1);
}

static void middle_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    if (safe_dup2_and_close(ctx->prev_fd, STDIN_FILENO) != 0)
        error_exit("dup2 failed (pipe read)");
    if (safe_dup2_and_close(ctx->pipefd[1], STDOUT_FILENO) != 0)
        error_exit("minishell: dup2 failed (pipe write)");
    close(ctx->pipefd[0]);
    execute_subcmd_with_redirs(subcmd, ctx->mini);
    exit(1);
}

static void first_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    if (cmd->next)
    {
        if (safe_dup2_and_close(ctx->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("minishell: dup2 failed (pipe write)");
        close(ctx->pipefd[0]);
    }
    execute_subcmd_with_redirs(subcmd, ctx->mini);
    exit(1); // se o execve falhar
}

void child_process(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (ctx->prev_fd == -1 && cmd == ctx->mini->head)
        first_child(cmd, ctx);
    else if (cmd->next)
        middle_child(cmd, ctx);
    else if (!cmd->next)
        last_child(cmd, ctx);
}
