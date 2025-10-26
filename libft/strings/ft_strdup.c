/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:36:57 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/27 08:21:44 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
/**
 * @brief Duplicates a string.
 *
 * Allocates memory for the copy, including the null terminator.
 *
 * @param src Input string.
 * @return Pointer to newly allocated string, or NULL on failure.
 */
char	*ft_strdup(const char *src)
{
	char	*buffer;
	int		sizesrc;

	if (!src)
		return (NULL);
	sizesrc = ft_strlen(src);
	buffer = malloc((sizesrc * sizeof(char)) + 1);
	if (buffer == NULL)
		return (NULL);
	ft_strcpy(buffer, src);
	return (buffer);
}
