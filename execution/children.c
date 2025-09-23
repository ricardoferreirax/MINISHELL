/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/23 21:53:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

static void first_child(t_cmd *cmd, t_pipeline *pp)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (cmd->next)
    {
        if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
            error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
        close(pp->pipefd[0]);
    }
    execute_subcommand(subcmd, pp->mini);
}

static void middle_child(t_cmd *cmd, t_pipeline *pp)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
        error_exit("MiNyanShell :3 : dup2 failed (pipe read)");
    if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
        error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
    close(pp->pipefd[0]);
    execute_subcommand(subcmd, pp->mini);
}

static void last_child(t_cmd *cmd, t_pipeline *pp)
{
    t_subcmd *subcmd;

    subcmd = cmd->head;
    if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
        error_exit("MiNyanShell :3 : dup2 failed (pipe read)");

    execute_subcommand(subcmd, pp->mini);
}

void child_process(t_cmd *cmd, t_pipeline *pp)
{
    if (pp->prev_pipefd == -1 && cmd == pp->mini->head)
        first_child(cmd, pp);
    else if (cmd->next)
        middle_child(cmd, pp);
    else if (!cmd->next)
        last_child(cmd, pp);
}
