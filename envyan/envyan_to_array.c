/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:37:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:25:30 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"

static char	*create_envyan_array_entry(char *key, char *value)
{
	char	*entry;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(key);
	val_len = 0;
	if (value)
		val_len = ft_strlen(value);
	entry = malloc(key_len + val_len + 2);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, key, key_len + 1);
	ft_strlcat(entry, "=", key_len + 2);
	if (value)
		ft_strlcat(entry, value, key_len + val_len + 2);
	return (entry);
}

static int	process_envyan_entry_to_array(t_envyan *current, char **env_array,
		int index)
{
	if (current->value == NULL)
		return (index);
	env_array[index] = create_envyan_array_entry(current->key, current->value);
	if (!env_array[index])
	{
		clean_envyan_array(env_array, index);
		return (-1);
	}
	return (index + 1);
}

static int	count_envyan_entries(t_envyan *envyan)
{
	int	count;

	count = 0;
	while (envyan)
	{
		count++;
		envyan = envyan->next;
	}
	return (count);
}

char	**envyan_to_array(t_envyan *envyan)
{
	int			count;
	t_envyan	*current;
	char		**env_array;
	int			i;

	count = count_envyan_entries(envyan);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = envyan;
	i = 0;
	while (current)
	{
		i = process_envyan_entry_to_array(current, env_array, i);
		if (i == -1)
			return (NULL);
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
