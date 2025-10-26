/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:53:20 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

/**
 * @brief Creates a new string resulting from applying a
 * function to each character.
 *
 * @param s Input string.
 * @param f Function to apply: receives index and character,
 * returns new character.
 * @return Newly allocated string, or NULL on failure.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s1;

	i = 0;
	if (!s)
		return (NULL);
	s1 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s1)
		return (NULL);
	while (s[i] != '\0')
	{
		s1[i] = f(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
