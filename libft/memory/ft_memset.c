/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:48:35 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:15 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
 * @brief Fills a memory area with a constant byte.
 *
 * @param ptr Pointer to the memory area.
 * @param value Byte to set (converted to unsigned char).
 * @param size Number of bytes to fill.
 * @return Pointer to the memory area.
 */
void	*ft_memset(void *a, int c, size_t i)
{
	size_t			j;
	unsigned char	*str;

	if (!a)
		return (NULL);
	str = (unsigned char *)a;
	j = 0;
	while (j < i)
	{
		str[j] = (unsigned char)c;
		j++;
	}
	return (a);
}
