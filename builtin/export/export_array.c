/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:27:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:06:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/envyan.h"

static void	add_value_to_entry(char *entry, t_envyan *var, int key_len)
{
	int	value_len;
	int	i;

	if (!var || !var->value)
		return ;
	value_len = ft_strlen(var->value);
	i = key_len;
	entry[i++] = '=';
	entry[i++] = '"';
	ft_strlcpy(entry + i, var->value, value_len + 1);
	i += value_len;
	entry[i++] = '"';
	entry[i] = '\0';
}

static char	*create_export_entry(t_envyan *var)
{
	char	*entry;
	int		key_len;
	int		value_len;
	int		total_len;

	if (!var || !var->key)
		return (NULL);
	key_len = ft_strlen(var->key);
	value_len = 0;
	if (var->value)
		value_len = ft_strlen(var->value);
	total_len = key_len;
	if (var->value)
		total_len += value_len + 3;
	entry = malloc(total_len + 1);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, var->key, key_len + 1);
	if (var->value)
		add_value_to_entry(entry, var, key_len);
	return (entry);
}

static int	fill_export_array(t_envyan *head, char **array)
{
	int			i;
	t_envyan	*current;

	i = 0;
	current = head;
	while (current)
	{
		if (!(current->key && ft_strcmp(current->key, "_") == 0
				&& current->value != NULL))
		{
			array[i] = create_export_entry(current);
			if (!array[i])
				return (-1);
			i++;
		}
		current = current->next;
	}
	array[i] = NULL;
	return (0);
}

static int	count_export_vars(t_envyan *envyan)
{
	t_envyan	*current_var;
	int			num_vars;
	int			should_skip;

	num_vars = 0;
	current_var = envyan;
	while (current_var)
	{
		should_skip = 0;
		if (current_var->key && ft_strcmp(current_var->key, "_") == 0
			&& current_var->value != NULL)
			should_skip = 1;
		if (!should_skip)
			num_vars++;
		current_var = current_var->next;
	}
	return (num_vars);
}

char	**create_export_array(t_envyan *head)
{
	int		count;
	char	**export_array;

	if (!head)
		return (NULL);
	count = count_export_vars(head);
	export_array = malloc(sizeof(char *) * (count + 1));
	if (!export_array)
		return (NULL);
	if (fill_export_array(head, export_array) == -1)
	{
		free(export_array);
		return (NULL);
	}
	return (export_array);
}
