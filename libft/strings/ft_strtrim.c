/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:49:08 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

static int	ft_iset(const char *set, char a)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (a == set[i])
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Trims all characters in set from the start and end of s1.
 *
 * @param s1 Input string.
 * @param set Set of characters to trim.
 * @return Newly allocated trimmed string, or NULL on failure.
 */
char	*ft_strtrim(const char *s1, char const *set)
{
	int		i;
	int		f;
	int		k;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	f = ft_strlen(s1);
	while (s1[i] && ft_iset(set, s1[i]))
		i++;
	while (f > i && ft_iset(set, s1[f - 1]))
		f--;
	str = malloc(sizeof(char) * ((f - i) + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (i < f)
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	str[k] = '\0';
	return (str);
}

// int	main(void)
// {
// 	char	*s1;
// 	char	*b;
// 	char	*s2;

// 	s1 = "   xxx aaaaaaaaaaaaaaa  xxx";
// 	b = " x";
// 	s2 = ft_strtrim(s1, b);
// 	printf("%s", s2);
// }
