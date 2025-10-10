/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:18:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/10 20:19:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

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