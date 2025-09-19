/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:31:38 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:39 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/// @brief Compares 2 memories fo x bytes and returns the difference
/// @param s1 memory to be compared
/// @param s2 memory to compare
/// @param n bytes to compare
/// @return 0 if they are equal, positive if s1 is bigger than s2 and vice versa
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	if (!s1 || !s2)
		return (0);
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (i < n)
	{
		if (a[i] != b[i])
		{
			return (a[i] - b[i]);
		}
		i++;
	}
	return (0);
}
