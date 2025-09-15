/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:19:34 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:33 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memcpy(void *dest, const void *src, size_t i)
{
	size_t			j;
	unsigned char	*str;
	unsigned char	*strdest;

	if (dest == NULL || src == NULL)
		return (NULL);
	str = (unsigned char *)src;
	strdest = (unsigned char *)dest;
	j = 0;
	while (j < i)
	{
		strdest[j] = str[j];
		j++;
	}
	return (dest);
}
