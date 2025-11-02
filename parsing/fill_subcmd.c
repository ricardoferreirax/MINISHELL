/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:56:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/02 12:32:03 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	add_arg(t_cmd *subcmd, const char *token)
{
	int		count;
	int		i;
	char	**new_arg;

	if (!subcmd || !token)
		return (1);
	count = 0;
	if (subcmd->args)
	{
		while (subcmd->args[count])
			count++;
	}
	new_arg = (char **)malloc((count + 2) * sizeof(char *));
	if (!new_arg)
		return (-1);
	i = 0;
	while (i < count) // copia osponteiros antigos
	{
		new_arg[i] = subcmd->args[i];
		i++;
	}
	new_arg[count] = ft_strdup(token);
	if (!new_arg[count])
	{
		free(new_arg);
		return (-1);
	}
	new_arg[count + 1] = NULL;
	if (subcmd->args)
		free(subcmd->args);
	subcmd->args = new_arg;
	return (0);
}
