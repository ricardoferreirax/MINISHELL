/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:14:56 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

/**
 * @brief Copies the next word from a string (delimited by c)
 * and advances pointer.
 *
 * @param s Pointer to input string (will be updated to point after copied word).
 * @param c Delimiter character.
 * @return Newly allocated word string, or NULL on allocation failure.
 */
char	*ft_wordcpy(const char **s, char c)
{
	char	*dest;
	int		counter;

	counter = 0;
	while ((**s == c) && (**s != '\0'))
		(*s)++;
	while ((**s != c) && (**s != '\0'))
	{
		counter++;
		(*s)++;
	}
	dest = malloc(sizeof(char) * (counter + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, ((*s) - counter), counter + 1);
	return (dest);
}
