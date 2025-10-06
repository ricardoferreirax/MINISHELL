/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:09:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 02:42:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

int	check_special_env_var(char *entry, char *var_name, int name_len)
{
	if (ft_strncmp(entry, var_name, name_len) == 0)
		return (1);
	return (0);
}

void	add_envyan_node(t_envyan **env_list, t_envyan **current, t_envyan *new_node)
{
	if (!*env_list)
		*env_list = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}

static void	split_envyan_entry(char *entry, char **key, char **value)
{
	char	*equals_sign;

	equals_sign = ft_strchr(entry, '=');
	if (equals_sign)
	{
		*equals_sign = '\0';
		*key = entry;
		*value = equals_sign + 1;
	}
	else
	{
		*key = entry;
		*value = NULL;
	}
}

void	process_envyan_entry(char *entry, t_envyan **env_list, t_envyan **current)
{
	char	*key;
	char	*value;
	t_envyan	*new_node;

	split_envyan_entry(entry, &key, &value);
	new_node = create_envyan_node(key, value);
	if (!new_node)
		return ;
	add_envyan_node(env_list, current, new_node);
}

t_envyan	*init_envyan(char **envp)
{
	t_envyan	*envyan_list;
	t_envyan	*node;
	int		        i;
	int		    shlvl;

	envyan_list = NULL;
	node = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	shlvl = get_shlvl_from_envp(envp);
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], "SHLVL=", 6) == 0))
            process_envyan_entry(envp[i], &envyan_list, &node);
        i++;
	}
	node = process_shlvl(&envyan_list, &node, shlvl);
	return (envyan_list);
}
