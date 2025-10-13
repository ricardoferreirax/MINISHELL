/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:18:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/13 15:54:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

void	free_envyan(t_envyan **head)
{
	t_envyan	*cur;
	t_envyan	*next;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*head = NULL;
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