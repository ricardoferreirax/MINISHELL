/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:30:15 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

/**
 * @brief Copies src to dest, up to size-1 characters, null-terminated.
 *
 * @param dest Destination buffer.
 * @param scr Source string.
 * @param size Size of the destination buffer.
 * @return Length of source string.
 */
unsigned int	ft_strlcpy(char *dest, const char *scr, size_t size)
{
	size_t	i;
	size_t	p;

	i = 0;
	p = 0;
	while (scr[p] != '\0')
		p++;
	if (size == 0)
		return (p);
	while (scr[i] != '\0' && i < size - 1)
	{
		dest[i] = scr[i];
		i++;
	}
	dest[i] = '\0';
	return (p);
}
