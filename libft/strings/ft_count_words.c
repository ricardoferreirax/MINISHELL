/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:15:59 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

/// @brief Count number of words in a string separated by a delimiter
/// @param s string
/// @param c delimiter
/// @return number of words
int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;
	bool	word;

	i = 0;
	word = false;
	count = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			word = false;
		else if (!word)
		{
			word = true;
			count++;
		}
		i++;
	}
	return (count);
}
