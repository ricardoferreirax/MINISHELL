/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:07:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/23 22:28:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (true);
	return (false);
}

bool builtin_runs_in_parent(t_subcmd *subcmd)
{
    if (!subcmd || !subcmd->args || !subcmd->args[0])
        return (false);
    if (ft_strcmp(subcmd->args[0], "cd") == 0
        || ft_strcmp(subcmd->args[0], "export") == 0
        || ft_strcmp(subcmd->args[0], "unset") == 0
        || ft_strcmp(subcmd->args[0], "exit") == 0)
        return (true);
    return (false);
}

int exec_builtin(t_subcmd *subcmd, t_mini *mini)
{
    char *cmd;

    if (!subcmd || !subcmd->args || !subcmd->args[0])
        return (0);
    cmd = subcmd->args[0];
    if (ft_strcmp(cmd, "echo") == 0)
        return ft_echo(subcmd, mini);
    else if (ft_strcmp(cmd, "pwd") == 0)
        return ft_pwd(subcmd, mini);
    else if (ft_strcmp(cmd, "env") == 0)
        return ft_env(subcmd, mini);
    else if (ft_strcmp(cmd, "exit") == 0)
        return ft_exit(subcmd, mini);
    else if (ft_strcmp(cmd, "export") == 0)
        return ft_export(subcmd, mini);
    else if (ft_strcmp(cmd, "unset") == 0)
        return ft_unset(subcmd, mini);
    else if (ft_strcmp(cmd, "cd") == 0)
        return ft_cd(subcmd, mini);
    return (1);
}

