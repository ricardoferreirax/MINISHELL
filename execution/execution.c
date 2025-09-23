/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/23 16:48:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"
# include "../MiNyanShell.h"

static char	**ft_parse_cmd(char *cmd)
{
	char	**cmd_list;

	cmd_list = ft_split_quotes(cmd, ' ');
	if (!cmd_list || !cmd_list[0])
	{
		ft_free_str(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}

static void set_subcmd_type(t_subcmd *subcmd)
{
    char *cmd_arg;

    if (!subcmd)
        return;
    if (!subcmd->args && subcmd->cmd) // se houver comando mas não houver args
        subcmd->args = ft_parse_cmd(subcmd->cmd);
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

static void prepare_pipeline_subcmds(t_cmd *cmd_list)
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

/* int ft_execution(t_cmd *cmd_list, t_mini *mini)
{
    int         status;
    t_subcmd    *subcmd;

    status = 0;
    if (!cmd_list || !cmd_list->head || !mini)
        return (0);
    prepare_pipeline_subcmds(cmd_list);
    subcmd = cmd_list->head;
    if (!cmd_list->next)
    {
        if (!subcmd->args || !subcmd->args[0])
            status = 0;
        else if (subcmd->cmd_type == BUILTIN_CMD)
        {
            if (builtin_runs_in_parent(subcmd)) // se for um builtin que altera o estado do shell
                status = execute_parent_builtin_with_redirs(subcmd, mini); // executa cd, export, unset, exit no parent
            else  // se for um builtin que não altera o estado do shell
                status = execute_single_cmd(subcmd, mini); // executa echo, pwd, env no child
        }
        else // se for um comando externo
            status = execute_single_cmd(subcmd, mini);
    }
    else
        status = ft_pipeline(cmd_list, mini);
    mini->last_status = status;
    return (status);
} */


int	handle_commands(t_mini *mini)
{
	t_cmd	*cmd;
    t_cmd   *tmp;
	int		has_pipeline;

	if (!mini || !mini->head)
		return (0);
	cmd = mini->head;
	if (!cmd->head || !cmd->head->args || !cmd->head->args[0])
		return (0);
	has_pipeline = 0;
	tmp = cmd;
	while (tmp && tmp->next)
	{
		has_pipeline = 1;
		tmp = tmp->next;
	}
	if (has_pipeline)
		return (execute_pipeline(cmd, mini));
	return (execute_single(cmd->head, mini));
}


