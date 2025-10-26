/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:32:05 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:14:10 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
 * @brief Copies a memory area to another, handling overlapping regions.
 *
 * @param dest Pointer to the destination memory.
 * @param src Pointer to the source memory.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory.
 */
void	*ft_memmove(void *dest, const void *src, size_t i)
{
	size_t			k;
	size_t			len;
	unsigned char	*source;
	unsigned char	*destin;

	if (dest == NULL || src == NULL)
		return (NULL);
	destin = (unsigned char *)dest;
	source = (unsigned char *)src;
	len = i;
	if (destin > source)
	{
		while (len--)
			destin[len] = source[len];
	}
	else
	{
		k = 0;
		while (k < i)
		{
			destin[k] = source[k];
			k++;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char buffer1[] = "1234567890";
// 	char buffer2[] = "12345678901234567890";
// 	char buffer3[] = "1234567890";
// 	char buffer4[] = "12345678901234567890";

// 	ft_memmove(buffer1, buffer2, ft_strlen(buffer1));
// 	memmove(buffer3, buffer4, ft_strlen(buffer3));

// 	printf("%s\n", buffer1);
// 	printf("%s\n", buffer3);
// }
