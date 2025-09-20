/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/20 15:38:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"
# include "../MiNyanShell.h"

static void	detect_subcmd_type(t_subcmd *subcmd)
{
	char *cmd_arg;

	if (!subcmd->args || !subcmd->args[0])
	{
		subcmd->cmd_type = CMD_EMPTY;
		return ;
	}
	cmd_arg = subcmd->args[0];
	if (is_it_builtin(cmd_arg))
		subcmd->cmd_type = CMD_BUILTIN;
	else if (cmd_arg[0] == '/')
		subcmd->cmd_type = CMD_ABS_PATH;
	else if ((cmd_arg[0] == '.' && cmd_arg[1] == '/')
		|| (cmd_arg[0] == '.' && cmd_arg[1] == '.' && cmd_arg[2] == '/'))
		subcmd->cmd_type = CMD_REL_PATH;
	else
		subcmd->cmd_type = CMD_SIMPLE;
}

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

static void	iterate_cmd_list(t_cmd *cmd_list)
{
	t_cmd		*node;
	t_subcmd	*subcmd;

	node = cmd_list;
	while (node)
	{
		subcmd = node->head;
		while (subcmd)
		{
			if (!subcmd->args && subcmd->cmd)
				subcmd->args = ft_parse_cmd(subcmd->cmd);
			detect_subcmd_type(subcmd);
			subcmd = subcmd->next;
		}
		node = node->next;
	}
}

int	ft_execution(t_cmd *cmd_list, t_mini *mini)
{
    int			status;
    t_subcmd	*subcmd;
    
    if (!cmd_list || !cmd_list->head)
        return (0);
    iterate_cmd_list(cmd_list);        
    subcmd = cmd_list->head;
    status = 0;
    if (!cmd_list->next) // comando único
	{
    	if (subcmd->cmd_type == CMD_BUILTIN && builtin_runs_in_parent(subcmd))
        	status = exec_builtin(subcmd, mini); // corre no parent
    	else
        	status = exec_subcmd(subcmd, mini);  // corre num child (builtin "safe" ou externo)
	}
    else // pipeline
        status = ft_pipeline(cmd_list, mini);
    mini->last_status = status;        
    return (status);
}
