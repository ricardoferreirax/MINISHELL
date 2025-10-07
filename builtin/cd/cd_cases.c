/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:06:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 13:33:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../../include/MiNyanShell.h"
#include "../../include/execution.h"
#include "../../include/builtin.h"
#include "../../include/envyan.h"

int	update_pwd_after_chdir(t_mini *mini)
{
	char	*current_path;

	if (!mini)
		return (1);
	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		perror("MiNyanShell: cd: getcwd failed");
		mini->last_status = 1;
		return (1);
	}
	set_pwd_from_path(mini, current_path);
	free(current_path);
	mini->last_status = 0;
	return (0);
}

int	cd_to_parent(t_mini *mini)
{
	if (chdir("..") != 0)
	{
		perror("Minyanshell: Error changing directory to parent!");
		mini->last_status = 1;
		return (1);
	}
	return (update_pwd_after_chdir(mini));
}

int	cd_to_oldpwd(t_mini *mini)
{
	char	*oldpwd_path;

	oldpwd_path = get_envyan(mini, "OLDPWD");
	if (!oldpwd_path)
	{
		ft_putendl_fd("Minyanshell: cd: OLDPWD not set", 2);
		mini->last_status = 1;
		return (1);
	}
	if (chdir(oldpwd_path) != 0)
	{
		perror("minishell: cd");
		free(oldpwd_path);
		mini->last_status = 1;
		return (1);
	}
	ft_putendl_fd(oldpwd_path, STDOUT_FILENO);
	free(oldpwd_path);
	return (update_pwd_after_chdir(mini));
}

int	cd_to_home(t_mini *mini)
{
	char	*home_path;

	home_path = get_envyan(mini, "HOME");
	if (!home_path)
	{
		ft_putendl_fd("MiNyanshell: cd: HOME not set", 2);
		mini->last_status = 1;
		return (1);
	}
	if (chdir(home_path) != 0)
	{
		perror("MiNyanshell: Error changing directory to HOME!");
		free(home_path);
		mini->last_status = 1;
		return (1);
	}
	free(home_path);
	return (update_pwd_after_chdir(mini));
}
