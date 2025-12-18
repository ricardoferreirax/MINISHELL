/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:07:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:29:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_cmd *cmd, t_mini *mini)
{
	int	status;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		mini->last_status = 1;
		return (1);
	}
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = ft_pwd(cmd, mini);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		status = ft_env(cmd, mini);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = ft_cd(mini, cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = ft_export(cmd, mini);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = ft_unset(cmd, mini);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		status = ft_exit(cmd, mini);
	else
		status = 1;
	mini->last_status = status;
	return (status);
}

int	builtin_has_io(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	return (0);
}
