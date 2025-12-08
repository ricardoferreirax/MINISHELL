/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:18:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 13:22:31 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

void free_envyan(t_envyan **head)
{
    t_envyan *current;
    t_envyan *next;

    if (!head || !*head)
        return ;
    current = *head;
    while (current)
    {
        next = current->next;
        if (current->key)
            free(current->key);
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
    *head = NULL;
}

void clean_envyan_array(char **envyan_array, int index)
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

