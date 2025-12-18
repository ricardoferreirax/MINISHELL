/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:29:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:25:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

t_envyan	*create_envyan_node(char *key, char *value)
{
	t_envyan	*new_node;

	if (!key)
		return (NULL);
	new_node = malloc(sizeof(t_envyan));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), NULL);
	new_node->value = NULL;
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), free(new_node), NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

char	*envyan_get_value(t_envyan *head, char *key)
{
	t_envyan	*current;

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

t_envyan	*get_last_envyan(t_envyan *head)
{
	t_envyan	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void	add_envyan_node(t_envyan **head, t_envyan **last, t_envyan *new_node)
{
	if (!new_node || !head || !last)
		return ;
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		*last = new_node;
	}
	else
	{
		if (!*last)
			*last = get_last_envyan(*head);
		(*last)->next = new_node;
		*last = new_node;
	}
}

int	envyan_key_exists(t_envyan *envyan, char *key)
{
	t_envyan	*current;

	current = envyan;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
