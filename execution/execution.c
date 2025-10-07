/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 15:08:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
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
        if (status == -1)                                 // se não era builtin
            status = run_external_single(cmd_list, mini); // tenta executar como comando externo
        return (status);
    }
    return (execute_pipeline(cmd_list, mini));            // num_cmds > 1
}

static int pre_execution(t_cmd *head, t_mini *mini)
{
    t_cmd *first;

    if (!head)
        return (0);
    if (process_all_heredocs(head, mini) != 0)  // processa TODOS os heredocs do pipeline antes de executar
        return (1);
    first = head;  // primeiro comando do pipeline
    if ((!first->cmd_args || !first->cmd_args[0]) && first->redirs && !first->next) // só redireções (sem args e sem pipeline)
        return run_redirs_without_cmd(first, mini);
    if ((!first->cmd_args || !first->cmd_args[0]) && !first->redirs) // comando vazio (sem args e sem redirs)
        return (0);
    return (-1); // it's totally fineeee
}

int ft_execution(t_cmd *cmd_list, t_mini *mini)
{
    int pre_exec;
    int status;

    if (!mini || !cmd_list)
    {
        if (mini)
            mini->last_status = 0;
        return (0);
    }
    // set_noninteractive_signals();
    pre_exec = pre_execution(cmd_list, mini);
    if (pre_exec != -1)
    {
        // set_signals();
        mini->last_status = pre_exec;
        return (pre_exec);
    }
    status = execute_cmds(cmd_list, mini);
    mini->last_status = status;
    // set_interactive_signals();
    return (status);
}
