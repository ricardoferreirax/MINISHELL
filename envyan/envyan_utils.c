/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:29:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:42:25 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"

t_envyan	*create_envyan_node(char *key, char *value)
{
	t_envyan	*new_node;

	new_node = malloc(sizeof(t_envyan));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

char *envyan_get_value(t_envyan *head, char *key)
{
    t_envyan *current;

    if (!key)
        return (NULL);
    current = head;
    while (current)
    {
        if (current->key && ft_strcmp(current->key, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

void	clean_envyan_array(char **envyan_array, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(envyan_array[i]);
		i++;
	}
	free(envyan_array);
}

void	add_envyan_node(t_envyan **env_list, t_envyan **current, t_envyan *new_node)
{
	if (!*env_list)
		*env_list = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}

void	free_envyan(t_envyan *envyan)
{
	t_envyan	*tmp;

	while (envyan)
	{
		tmp = envyan;
		envyan = envyan->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
