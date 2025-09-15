/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:37:40 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:55 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/// @brief Alocate memory of size x to n menbers of an array
/// @param nmemb number of members
/// @param size size of each member
/// @return buffer whit size and 0 in each index
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if ((nmemb == 0 || size == 0))
		return (malloc(0));
	if (nmemb > (SIZE_MAX) / size)
		return (NULL);
	buffer = malloc(nmemb * size);
	if (buffer == NULL)
		return (NULL);
	ft_bzero(buffer, nmemb * size);
	return (buffer);
}

// int main()
// {
// 	int *buffer;
// 	int	*real;
// 	buffer = (int *)ft_calloc(0, 0);
// 	real = (int *)calloc(0, 0);
// 	printf("%d\n ", buffer[0]);
// }