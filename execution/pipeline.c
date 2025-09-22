/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:57:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/21 18:58:49 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

static void parent_process(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (ctx->prev_fd != -1) // se existir prev_fd
        close(ctx->prev_fd); // fecha o prev_fd (read end do pipe anterior)
    if (cmd->next)
    {
        close(ctx->pipefd[1]);
        ctx->prev_fd = ctx->pipefd[0];
    }
}

static int handle_command(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (cmd->next)
    {
        if (pipe(ctx->pipefd) == -1)
            error_exit("minishell: pipe failed");
    }
    ctx->pid = fork();
    if (ctx->pid < 0)
        error_exit("minishell: fork failed");
    if (ctx->pid == 0) // CHILD
        child_process(cmd, ctx);
    else if (ctx->pid > 0) // PARENT
        parent_process(cmd, ctx);
    return (0);
}

int ft_pipeline(t_cmd *cmds, t_mini *mini)
{
    t_exec_cmd ctx;

    ctx.prev_fd = -1;
    ctx.mini = mini;
    while (cmds) // para cada comando na lista
    {
        handle_command(cmds, &ctx);
        cmds = cmds->next;
    }
    wait_for_children(mini, ctx.pid); // espera pelo último child process
    return (mini->last_status);
}
