/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_chararr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:11:04 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:50 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/// @brief Frees all memory allocated for an array
/// @param array array to be freed
void	free_chararr(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
