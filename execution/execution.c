/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/08 16:41:42 by pfreire-         ###   ########.fr       */
=======
/*   Updated: 2025/10/09 09:23:17 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int number_of_cmds(t_cmd *cmd_list)
{
    t_cmd *current_cmd;
    int    num_cmds;

    if (!cmd_list)
        return (0);
    current_cmd = cmd_list;
    num_cmds = 0;
    while (current_cmd)
    {
        num_cmds++;
        current_cmd = current_cmd->next;
    }
    return (num_cmds);
}

static int execute_cmds(t_cmd *cmd_list, t_mini *mini)
{
    int num_cmds;
    int status;

    num_cmds = number_of_cmds(cmd_list);
    if (num_cmds == 0)
        return (0);
    if (num_cmds == 1)
    {
        status = execute_single_cmd(cmd_list, mini);
        if (status == NOT_BUILTIN)
            status = execute_external_cmd(cmd_list, mini);
        return (status);
    }
    return (execute_multiple_cmds(cmd_list, mini));
}

static int pre_execution(t_cmd *head, t_mini *mini)
{
    t_cmd *first;

    if (!head)
        return (NO_CMD);
    if (process_all_heredocs(head, mini) != 0)
        return (ERROR);
    first = head;  // primeiro comando da pipeline
    if ((!first->args || !first->args[0]) && first->redirs && !first->next)
        return (execute_redirs_without_cmd(first, mini));
    if ((!first->args || !first->args[0]) && !first->redirs)
        return (NO_CMD);
    return (CONTINUE);
}

int execute_pipeline(t_cmd *cmd_list, t_mini *mini)
{
    int pre_exec;
    int status;

    if (!mini || !cmd_list)
    {
        mini->last_status = 0;
        return (0);
    }
    // set_noninteractive_signals();
    pre_exec = pre_execution(cmd_list, mini);
    if (pre_exec != CONTINUE)
    {
        // set_signals();
        close_all_heredoc_fds(cmd_list);
        mini->last_status = pre_exec;
        return (pre_exec);
    }
    status = execute_cmds(cmd_list, mini);
    mini->last_status = status;
    // set_interactive_signals();
    close_all_heredoc_fds(cmd_list);
    return (status);
}
