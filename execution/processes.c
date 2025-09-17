/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/17 17:05:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

void first_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *sub;
    
    sub = cmd->head;
    if (cmd->next) // se houver próximo comando
        dup2(ctx->pipefd[1], STDOUT_FILENO); // aponta/liga o stdout para o pipe write end
    if (sub->in_fd != -1) // se veio do infile ou do heredoc
        dup2(sub->in_fd, STDIN_FILENO);
    close(ctx->pipefd[0]);
    close(ctx->pipefd[1]);
    ft_exec_cmd(sub, ctx->mini->env);
    exit(1); // se o execve falhar
}

void middle_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *sub;
    
    sub = cmd->head;
    dup2(prev_fd, STDIN_FILENO);
    if (cmd->next)  // se houver próximo comando
        dup2(ctx->pipefd[1], STDOUT_FILENO); // aponta/liga o stdout para o pipe write end
    close(ctx->prev_fd);
    close(ctx->pipefd[0]);
    close(ctx->pipefd[1]);
    ft_exec_cmd(sub, ctx->mini);
    exit(1);
}

void last_child(t_cmd *cmd, t_exec_cmd *ctx)
{
    t_subcmd *sub;

    sub = cmd->head; // o último comando
    dup2(ctx->prev_fd, STDIN_FILENO);  
    if (sub->out_fd != -1)
        dup2(sub->out_fd, STDOUT_FILENO);
    close(ctx->prev_fd);
    ft_exec_cmd(sub, ctx->mini->env);
    exit(1);
}

int execute_pipeline(t_cmd *cmds, t_mini *mini)
{
    int pipefd[2];
    int prev_fd = -1;
    pid_t pid;

    while (cmds)
    {
        if (cmds->next) // se houver próximo comando
            pipe(pipefd); // cria o pipe
        pid = fork(); // cria o processo
        if (pid == 0)
        {
            if (!prev_fd && cmds == mini->head) // se é o first command
                first_child(cmds, pipefd, mini);
            else if (cmds->next)  // se for um middle command
                middle_child(cmds, pipefd, prev_fd, mini);
            else if (!cmds->next) // se for o last command
                last_child(cmds, prev_fd, mini);
        }
        if (prev_fd != -1) // fecha o prev_fd se existir
            close(prev_fd);
        if (cmds->next) // se houver próximo comando
        {
            close(pipefd[1]);
            prev_fd = pipefd[0]; // o read end do pipe é o próximo prev_fd
        }
        cmds = cmds->next;
    }
    mini_wait(mini, pid); // espera pelo último filho
    return (mini->last_status);
}

