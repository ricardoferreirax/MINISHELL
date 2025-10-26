/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:56 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:45 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
 * @brief Searches for the first occurrence of a byte in memory.
 *
 * @param ptr Pointer to the memory area.
 * @param value Byte to search for (converted to unsigned char).
 * @param num Number of bytes to examine.
 * @return Pointer to the first occurrence, or NULL if not found.
 */
void	*ft_memchr(const void *a, int b, size_t c)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	if (!a)
		return (NULL);
	str = (unsigned char *)a;
	while (i < c)
	{
		if (str[i] == (unsigned char)b)
		{
			return (str + i);
		}
		i++;
	}
	return (NULL);
}
// int main()
// {
// 	char s[] = "helllo world";
// 	char *f;
// 	f = ft_memchr(s, 'l', 3);
// 	printf("%s\n", f);
// }
