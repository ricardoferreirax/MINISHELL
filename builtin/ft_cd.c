/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:21:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:09:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"
#include "../include/execution.h"

static char	*get_envyan(t_mini *mini, char *key)
{
	t_envyan	*node;

	if (!mini || !key)
		return (NULL);
	node = mini->envyan;
	while (node)
	{
		if (node->key && strcmp(node->key, key) == 0)
		{
			if (!node->value)
				return (NULL);
			return (ft_strdup(node->value));
		}
		node = node->next;
	}
	return (NULL);
}

static void	set_pwd_from_path(t_mini *mini, char *new_path)
{
	char	*prev_path;

	if (!mini || !new_path)
		return ;
	prev_path = get_envyan(mini, "PWD");
	if (prev_path)
	{
		set_envyan_key_value(mini, "OLDPWD", prev_path);
		free(prev_path);
	}
	set_envyan_key_value(mini, "PWD", new_path);
}

static int	update_pwd_after_chdir(t_mini *mini)
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

static int	cd_to_home(t_mini *mini)
{
	char	*home_path;

	if (!mini)
		return (1);
	home_path = get_envyan(mini, "HOME");
	if (!home_path || home_path[0] == '\0')
	{
		ft_putendl_fd("MiNyanshell: cd: HOME not set", STDERR_FILENO);
		if (home_path)
			free(home_path);
		mini->last_status = 1;
		return (1);
	}
	if (chdir(home_path) != 0)
	{
		perror("MiNyanshell: cd");
		free(home_path);
		mini->last_status = 1;
		return (1);
	}
	free(home_path);
	return (update_pwd_after_chdir(mini));
}

int	ft_cd(t_mini *mini, char **args)
{
	char	*target;

	if (!mini || !args)
		return (1);
	if (!args[1] || args[1][0] == '\0' || strcmp(args[1], "~") == 0)
		return (cd_to_home(mini));
	if (args[2])
	{
		ft_putendl_fd("MiNyanshell: cd: too many arguments", STDERR_FILENO);
		mini->last_status = 1;
		return (1);
	}
	target = args[1];
	if (chdir(target) != 0)
	{
		perror("MiNyanshell: cd");
		mini->last_status = 1;
		return (1);
	}
	return (update_pwd_after_chdir(mini));
}
