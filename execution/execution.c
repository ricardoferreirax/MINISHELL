/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/24 23:34:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"
# include "../MiNyanShell.h"

static int execute_cmd_list(t_cmd *cmd_list, t_mini *mini)
{
    int      status;
    t_subcmd *subcmd;

    subcmd = cmd_list->head;
    if (!cmd_list->next) // só um comando
    {
        if (!subcmd->args || !subcmd->args[0])
            status = 0;
        else if (subcmd->cmd_type == BUILTIN_CMD)
        {
            if (builtin_runs_in_parent(subcmd))
                status = execute_parent_builtin_with_redirs(subcmd, mini);
            else
                status = execute_single_cmd(subcmd, mini);
        }
        else
            status = execute_single_cmd(subcmd, mini);
    }
    else
        status = execute_pipeline(cmd_list, mini);

    return (status);
}

static int prepare_heredocs(t_cmd *cmd_list, t_mini *mini)
{
    int heredoc_status;

    if (!cmd_list || !cmd_list->head || !mini)
        return (1);
    heredoc_status = process_all_heredocs(cmd_list, mini);
    if (heredoc_status != 0)
    {
        mini->last_status = heredoc_status;
        return (heredoc_status); // aborta se falhar
    }
    return (0);
}

static void set_subcmd_type(t_subcmd *subcmd)
{
    char *cmd_arg;

    if (!subcmd->args || !subcmd->args[0])
    {
        subcmd->cmd_type = NONE_CMD;
        return;
    }
    cmd_arg = subcmd->args[0];
    if (is_builtin(cmd_arg))
        subcmd->cmd_type = BUILTIN_CMD;
    else if (cmd_arg[0] == '/')
        subcmd->cmd_type = ABS_PATH_CMD;
    else if ((cmd_arg[0] == '.' && cmd_arg[1] == '/') ||
             (cmd_arg[0] == '.' && cmd_arg[1] == '.' && cmd_arg[2] == '/'))
        subcmd->cmd_type = REL_PATH_CMD;
    else
        subcmd->cmd_type = SIMPLE_CMD;
}

static void iterate_subcmds(t_cmd *cmd_list)
{
    t_cmd    *cmd;
    t_subcmd *subcmd;

	cmd = cmd_list;
    while (cmd)
    {
        subcmd = cmd->head;
        while (subcmd)
        {
            set_subcmd_type(subcmd);
            subcmd = subcmd->next;
        }
        cmd = cmd->next;
    }
}

int ft_execution(t_cmd *cmd_list, t_mini *mini)
{
    int status;
    int heredoc_status;

    if (!cmd_list || !cmd_list->head || !mini)
        return (0);
    iterate_subcmds(cmd_list);
    if (prepare_heredocs(cmd_list, mini) != 0)
        return (mini->last_status);
    status = execute_cmd_list(cmd_list, mini);
    mini->last_status = status;
    return (status);
}
