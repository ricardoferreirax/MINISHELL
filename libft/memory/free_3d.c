/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:03:40 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/25 12:05:41 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
 * @brief Frees a NULL-terminated 3D array.
 *
 * @param arr Pointer to the 3D array to free.
 */
void	free_3d(void ***arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free_2d(arr[i]);
		i++;
	}
	free(arr);
}
