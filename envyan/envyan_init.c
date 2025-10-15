/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:09:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:42:17 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:09:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/11 12:46:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
>>>>>>> ricardo
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

<<<<<<< HEAD
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
=======
t_envyan *init_envyan(char **envp)
{
    t_envyan *envyan_list;
    t_envyan *last_node;
    t_envyan *new_node;
    char *key;
    char *value;
    int i;

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
>>>>>>> ricardo
}
