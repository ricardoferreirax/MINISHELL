/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 22:45:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"
# include "../MiNyanShell.h"

static int execute_cmds(t_cmd *cmd_list, t_mini *mini)
{
    int num_cmds;
    int status;

    num_cmds = init_pipeline(cmd_list);
    if (num_cmds == -1)
    {
        mini->last_status = 1;
        return (1);
    }
    if (num_cmds == 1)
    {
        status = execute_single_cmd(cmd_list->head, mini);
        if (status == -1) // não e um builtin então é um comando externo
            status = execute_external_cmd(cmd_list->head, mini);
    }
    else if (num_cmds > 1)
        status = execute_pipeline(cmd_list, mini);
    else // nenhum comando
        status = 0;
    // set_signals();
    return (status);
}

static void assign_subcmd_type(t_subcmd *subcmd)
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

static void set_subcmd_types(t_cmd *cmd_list)
{
    t_cmd    *cmd;
    t_subcmd *subcmd;

	cmd = cmd_list;
    while (cmd)
    {
        subcmd = cmd->head;
        while (subcmd)
        {
            assign_subcmd_type(subcmd);
            subcmd = subcmd->next;
        }
        cmd = cmd->next;
    }
}

static int pre_execution(t_cmd *cmd, t_mini *mini)
{
    t_subcmd *subcmd;

    if (!cmd || !cmd->head)
        return (EXEC_EMPTY);
    subcmd = cmd->head;
    if ((!subcmd->args || !subcmd->args[0]) && !subcmd->redirs) // comando vazio sem redireções
        return (EXEC_EMPTY);
    if ((!subcmd->args || !subcmd->args[0]) && subcmd->redirs && !cmd->next) // só redireções (sem args e sem pipeline)
        return (handle_single_redirection_only(cmd, mini));
    if (process_all_heredocs(cmd, mini) != 0) // processar os heredocs (só se não for vazio ou só redireções)
        return (EXEC_ERROR);
    return (EXEC_NORMAL);
}

int ft_execution(t_cmd *cmd_list, t_mini *mini)
{
    int check_result;
    int status;

    if (!cmd_list || !cmd_list->head || !mini)
        return (0);
    check_result = pre_execution(cmd_list, mini);
    if (check_result != EXEC_NORMAL)
	{
		// set_signals();
		mini->last_status = check_result;
        return (check_result);
	}
    set_subcmd_types(cmd_list);
    status = execute_cmds(cmd_list, mini);
    mini->last_status = status;
    return (status);
}
