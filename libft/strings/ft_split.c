/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:58:54 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/29 17:12:45 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

/**
 * @brief Splits a string into an array of strings using a delimiter.
 *
 * Allocates memory for each substring and the array of pointers.
 *
 * @param s Input string.
 * @param c Delimiter character.
 * @return Null-terminated array of substrings, or NULL on allocation failure.
 */
char	**ft_split(char const *s, char c)
{
	char	**array;
	int		wordnbr;
	int		i;

	i = -1;
	wordnbr = ft_count_words(s, c);
	array = malloc(sizeof(char *) * (wordnbr + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < wordnbr)
	{
		array[i] = ft_wordcpy(&s, c);
		if (array[i] == NULL)
			return (free_2d((void **)array), NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}
