/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envyan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:25:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:26:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static int	add_envyan_key_value(t_mini *mini, char *key, char *value)
{
	t_envyan	*new_entry;

	if (!mini || !key)
		return (1);
	new_entry = malloc(sizeof(t_envyan));
	if (!new_entry)
		return (1);
	new_entry->key = ft_strdup(key);
	if (!new_entry->key)
		return (free(new_entry), 1);
	if (value)
	{
		new_entry->value = ft_strdup(value);
		if (!new_entry->value)
			return (free(new_entry->key), free(new_entry), 1);
	}
	else
		new_entry->value = NULL;
	new_entry->next = mini->envyan;
	mini->envyan = new_entry;
	return (0);
}

static int	replace_envyan_value(t_mini *mini, char *key, char *value)
{
	t_envyan	*current;
	char		*dup;

	if (!mini || !key)
		return (-1);
	current = mini->envyan;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
		{
			dup = NULL;
			if (value)
			{
				dup = ft_strdup(value);
				if (!dup)
					return (-1);
			}
			if (current->value)
				free(current->value);
			current->value = dup;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	set_envyan_key_value(t_mini *mini, char *key, char *value)
{
	int	status;

	if (!mini || !key)
		return (1);
	status = replace_envyan_value(mini, key, value);
	if (status == 1)
		return (0);
	if (status == -1)
		return (1);
	return (add_envyan_key_value(mini, key, value));
}
