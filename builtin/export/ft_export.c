/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:06:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/envyan.h"
#include "../../include/execution.h"

static int	handle_single_export(t_mini *mini, char *arg)
{
	if (!mini || !arg || arg[0] == '\0')
		return (0);
	if (!validate_export_arg(arg))
		return (1);
	assign_envyan_key(mini, arg);
	return (0);
}

static void	print_and_free_export_array(char **export_entry)
{
	int	i;

	i = 0;
	if (!export_entry)
		return ;
	while (export_entry[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(export_entry[i], STDOUT_FILENO);
		free(export_entry[i]);
		i++;
	}
	free(export_entry);
}

static int	export_print_sorted(t_mini *mini)
{
	char	**export_entry;

	if (!mini)
		return (1);
	if (!mini->envyan)
	{
		mini->last_status = 0;
		return (0);
	}
	export_entry = create_export_array(mini->envyan);
	if (!export_entry)
	{
		mini->last_status = 1;
		return (1);
	}
	sort_export_entries(export_entry);
	print_and_free_export_array(export_entry);
	mini->last_status = 0;
	return (0);
}

static int	export_has_args(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	had_error;

	if (!mini)
		return (1);
	if (!export_has_args(cmd))
		return (export_print_sorted(mini));
	had_error = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
		{
			if (handle_single_export(mini, cmd->args[i]) != 0)
				had_error = 1;
		}
		i++;
	}
	mini->last_status = had_error;
	return (had_error);
}
