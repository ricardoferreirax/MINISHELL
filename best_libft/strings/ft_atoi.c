/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:12:09 by pfreire-          #+#    #+#             */
/*   Updated: 2025/04/14 11:02:36 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	signal;
	int	result;

	i = 0;
	result = 0;
	signal = 1;
	while ((s[i] && s[i] == ' ') || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		signal = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (0);
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		result *= 10;
		result += (s[i] - '0');
		i++;
	}
	return (result * signal);
}
// int main()
// {
// 	char *nptr;

// 	nptr = NULL;
// 	printf("%d\n", ft_atoi(nptr));
// 	printf("%ld\n", strtol(nptr, NULL, 10));
// 	printf("%d\n", atoi(nptr));
// }