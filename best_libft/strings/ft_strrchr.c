/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:44 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 13:53:15 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	*ft_strrchr(const char *a, int b)
{
	int	i;

	if (!a)
		return (NULL);
	i = ft_strlen(a);
	while (i >= 0)
	{
		if (a[i] == (char)b)
		{
			return ((char *)a + i);
		}
		i--;
	}
	return (NULL);
}
