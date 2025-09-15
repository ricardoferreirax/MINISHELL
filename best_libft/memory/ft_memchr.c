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

/// @brief Searchs for the first occurency of a int in memory in x bytes
/// @param a memory to search through
/// @param b int to be localized
/// @param c bytes to be searched
/// @return pointer to index or NULL if fails to find
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