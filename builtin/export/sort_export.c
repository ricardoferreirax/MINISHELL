/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:40:46 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:06:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/envyan.h"

static int	entry_len(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}

static int	swap_if_needed(char **a, char **b)
{
	char	*swap;

	if (!a || !b)
		return (0);
	if (ft_strcmp(*a, *b) > 0)
	{
		swap = *a;
		*a = *b;
		*b = swap;
		return (1);
	}
	return (0);
}

void	sort_export_entries(char **envyan_array)
{
	int	len;
	int	i;
	int	j;
	int	swapped;

	if (!envyan_array)
		return ;
	len = entry_len(envyan_array);
	i = 0;
	while (i < len - 1)
	{
		swapped = 0;
		j = 0;
		while (j < len - 1 - i)
		{
			if (swap_if_needed(&envyan_array[j], &envyan_array[j + 1]))
				swapped = 1;
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}
