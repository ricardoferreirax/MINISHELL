/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:09:00 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 12:50:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	*ft_strchr(const char *s, int b)
{
	int	i;

	i = 0;
	if ((char)b == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (char)b)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	char s[] = "bombardino crocodillo";
// 	printf("%s\n", ft_strchr(s, 'b'));
// }