/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:49:58 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/16 16:12:28 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/MiNyanShell.h"
#include "../include/signals.h"

static void prepare_external_or_exit(t_pipe_pos pos, t_cmd *cmd, t_pipeline *pp)
{
    int resolve_status;

    resolve_status = is_external_resolved(cmd, pp->mini);
    if (resolve_status <= 0)
	{
    	close_my_pipes(pos, pp);
    	if (resolve_status == NOT_FOUND)
    	{
        	cmd_not_found_msg(cmd->args[0]);
        	minyanshell_cleanup_and_exit(pp->mini, 127);
    	}
    	if (resolve_status == EXT_NO_PERM)
    	{
        	perror(cmd->args[0]);
        	minyanshell_cleanup_and_exit(pp->mini, 126);
    	}
    	minyanshell_cleanup_and_exit(pp->mini, 1);
	}
    if (pos == FIRST)
    {
        if (cmd->next)
            pp->need_next_stdout = 1;
    }
    else if (pos == MIDDLE)
    {
        if (cmd->next)
            pp->need_next_stdout = 1;
    }
}

void prepare_first(t_cmd *cmd, t_pipeline *pp)
{
    pp->need_prev_stdin = 0;
    pp->need_next_stdout = 0;

    if (!cmd || !cmd->args || !cmd->args[0])
    {
        close_my_pipes(FIRST, pp);
        minyanshell_cleanup_and_exit(pp->mini, 0);
    }
    if (is_builtin(cmd->args[0]))
    {
        if (!builtin_has_io(cmd->args[0]))
        {
            close_my_pipes(FIRST, pp);
            minyanshell_signals(CHILD_EXEC);
            minyanshell_cleanup_and_exit(pp->mini, execute_builtin(cmd, pp->mini));
        }
        if (cmd->next)
            pp->need_next_stdout = 1;
        return;
    }
    prepare_external_or_exit(FIRST, cmd, pp);
}

void prepare_middle(t_cmd *cmd, t_pipeline *pp)
{
    pp->need_prev_stdin = 1;
    pp->need_next_stdout = 0;

    if (cmd && cmd->next)
        pp->need_next_stdout = 1;
    if (!cmd || !cmd->args || !cmd->args[0])
    {
        close_my_pipes(MIDDLE, pp);
        minyanshell_cleanup_and_exit(pp->mini, 0);
    }
    if (is_builtin(cmd->args[0]))
    {
        if (!builtin_has_io(cmd->args[0]))
        {
            close_my_pipes(MIDDLE, pp);
            minyanshell_signals(CHILD_EXEC);
            minyanshell_cleanup_and_exit(pp->mini, execute_builtin(cmd, pp->mini));
        }
        return ;
    }
    prepare_external_or_exit(MIDDLE, cmd, pp);
}

void prepare_last(t_cmd *cmd, t_pipeline *pp)
{
    pp->need_prev_stdin = 1;
    pp->need_next_stdout = 0;

    if (!cmd || !cmd->args || !cmd->args[0])
    {
        close_my_pipes(LAST, pp);
        minyanshell_cleanup_and_exit(pp->mini, 0);
    }
    if (is_builtin(cmd->args[0]))
    {
        if (!builtin_has_io(cmd->args[0]))
        {
            close_my_pipes(LAST, pp);
            minyanshell_signals(CHILD_EXEC);
            minyanshell_cleanup_and_exit(pp->mini, execute_builtin(cmd, pp->mini));
        }
        return ;
    }
    prepare_external_or_exit(LAST, cmd, pp);
}
