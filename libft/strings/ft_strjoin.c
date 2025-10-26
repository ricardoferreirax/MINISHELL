/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:24:59 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

/**
 * @brief Concatenates two strings into a newly allocated string.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return Pointer to the newly allocated string, or NULL on failure.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r1;
	size_t	i;
	size_t	j;

	r1 = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!r1)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		r1[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		r1[i] = s2[j];
		i++;
		j++;
	}
	r1[i] = '\0';
	return (r1);
}

// int main()
// {
// 	char a[] = "hello";
// 	char b[] = "world";
// 	char *c;

// 	c = ft_strjoin(a, b);
// 	printf("%s", c);
// }
