/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:37:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:25:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static char	*create_envyan_array_entry(char *key, char *value)
{
	char	*entry;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(key);
	val_len = 0;
	if (value != NULL)
		val_len = ft_strlen(value);
	entry = malloc(key_len + 1 + val_len + 1);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, key, key_len + 1);
	ft_strlcat(entry, "=", key_len + 2);
	if (value != NULL)
		ft_strlcat(entry, value, key_len + 1 + val_len + 1);
	return (entry);
}

static int	fill_envyan_array(t_envyan *head, char **array)
{
	int			i;
	t_envyan	*current;

	i = 0;
	current = head;
	while (current)
	{
		if (current->value != NULL)
		{
			array[i] = create_envyan_array_entry(current->key, current->value);
			if (!array[i])
				return (-1);
			i++;
		}
		current = current->next;
	}
	array[i] = NULL;
	return (0);
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
	int		count;
	char	**env_array;

	if (!envyan)
		return (NULL);
	count = count_envyan_entries(envyan);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (fill_envyan_array(envyan, env_array) == -1)
	{
		free(env_array);
		return (NULL);
	}
	return (env_array);
}
