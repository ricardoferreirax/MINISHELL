/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:58:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/17 18:28:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

void first_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    if (cmd->next) // se houver próximo comando
        dup2(ctx->pipefd[1], STDOUT_FILENO); // aponta/liga o stdout para o pipe write end
    if (subcmd->in_fd != -1) // se veio do infile ou do heredoc
        dup2(subcmd->in_fd, STDIN_FILENO);
    close(ctx->pipefd[0]);
    close(ctx->pipefd[1]);
    ft_exec_cmd(subcmd, ctx->mini->env);
    exit(1); // se o execve falhar
}

void middle_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;
    
    subcmd = cmd->head;
    dup2(ctx->prev_fd, STDIN_FILENO);
    if (cmd->next)  // se houver próximo comando
        dup2(ctx->pipefd[1], STDOUT_FILENO); // aponta/liga o stdout para o pipe write end
    close(ctx->prev_fd);
    close(ctx->pipefd[0]);
    close(ctx->pipefd[1]);
    ft_exec_cmd(subcmd, ctx->mini->env);
    exit(1);
}

void last_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *subcmd;

    subcmd = cmd->head; // o último comando
    dup2(ctx->prev_fd, STDIN_FILENO);
    if (subcmd->out_fd != -1)
        dup2(subcmd->out_fd, STDOUT_FILENO);
    close(ctx->prev_fd);
    ft_exec_cmd(subcmd, ctx->mini->env);
    exit(1);
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
