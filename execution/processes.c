/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 10:36:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static void parent_process(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (ctx->prev_fd != -1) // se existir prev_fd
        close(ctx->prev_fd); // fecha o prev_fd (read end do pipe anterior)
    if (cmd->next) // se houver próximo comando
    {
        close(ctx->pipefd[1]);
        ctx->prev_fd = ctx->pipefd[0]; // o read end do pipe é o próximo prev_fd
    }
}

void last_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    safe_dup2_and_close(ctx->prev_fd, STDIN_FILENO);
    if (subcmd->out_fd != -1)  // se o output vai para o outfile
        safe_dup2_and_close(subcmd->out_fd, STDOUT_FILENO);
    ft_exec_cmd(subcmd, ctx->mini->env);
    exit(1);
}

void middle_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    safe_dup2_and_close(ctx->prev_fd, STDIN_FILENO);
    if (cmd->next)
        safe_dup2_and_close(ctx->pipefd[1], STDOUT_FILENO);
    close(ctx->pipefd[0]); // fecha o read end do pipe pois só vai escrever
    ft_exec_cmd(subcmd, ctx->mini->env);
    exit(1); 
}

void first_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    if (cmd->next)
        safe_dup2_and_close(ctx->pipefd[1], STDOUT_FILENO);
    if (subcmd->in_fd != -1) // se o input vem do infile (ou do heredoc)
        safe_dup2_and_close(subcmd->in_fd, STDIN_FILENO);
    close(ctx->pipefd[0]);
    ft_exec_cmd(subcmd, ctx->mini->env);
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
