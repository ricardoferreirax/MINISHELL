/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:27:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 21:39:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static int process_export_entry(t_envyan *current, char **envyan_array, int index)
{
    if (!current || !envyan_array)
        return (-1);
    if (current->key && ft_strcmp(current->key, "_") == 0 && current->value != NULL)
        return (index);
    envyan_array[index] = create_export_entry(current);
    if (!envyan_array[index])
    {
        cleanup_envyan_array(envyan_array, index);
        return (-1);
    }
    return (index + 1);
}

int count_export_vars(t_envyan *envyan)
{
    int count;
    int skip;

    count = 0;
    while (envyan)
    {
        skip = 0;
        if (envyan->key && ft_strcmp(envyan->key, "_") == 0 && envyan->value != NULL)
            skip = 1;
        if (!skip)
            count++;
        envyan = envyan->next;
    }
    return (count);
}

char **envyan_to_export_array(t_envyan *head)
{
    int        count;
    char     **envyan_array;
    int        i;
	int        next_i;
    t_envyan  *current;

    count = count_export_vars(head);
    envyan_array = malloc(sizeof(char *) * (count + 1));
    if (!envyan_array)
        return (NULL);
    current = head;
    i = 0;
    while (current)
    {
        next_i = process_export_entry(current, envyan_array, i);
        if (next_i == -1)
        {
			free(envyan_array);
            return (NULL);
        }
        i = next_i;
        current = current->next;
    }
    envyan_array[i] = NULL;
    return (envyan_array);
}
