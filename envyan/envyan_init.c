/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:09:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:26:47 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static void	split_envyan_entry(char *entry, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(entry, '=');
	if (equal)
	{
		*equal = '\0';
		*key = entry;
		*value = equal + 1;
	}
	else
	{
		*key = entry;
		*value = NULL;
	}
}

static void	process_env_entry(char *env, t_envyan **list, t_envyan **last)
{
	t_envyan	*new;
	char		*key;
	char		*value;

	split_envyan_entry(env, &key, &value);
	new = create_envyan_node(key, value);
	if (new)
		add_envyan_node(list, last, new);
}

t_envyan	*init_envyan(char **envp)
{
	t_envyan	*list;
	t_envyan	*last;
	int			i;

	list = NULL;
	last = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) != 0)
			process_env_entry(envp[i], &list, &last);
		i++;
	}
	return (list);
}

/* t_envyan	*init_envyan(char **envp)
{
	t_envyan	*envyan_list;
	t_envyan	*last_node;
	t_envyan	*new_node;
	char		*key;
	char		*value;
	int			i;

	envyan_list = NULL;
	last_node = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) != 0)
		{
			split_envyan_entry(envp[i], &key, &value);
			new_node = create_envyan_node(key, value);
			if (new_node)
				add_envyan_node(&envyan_list, &last_node, new_node);
		}
		i++;
	}
	return (envyan_list);
} */
