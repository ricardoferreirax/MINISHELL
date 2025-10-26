/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:03:37 by pfreire-          #+#    #+#             */
/*   Updated: 2025/10/08 17:03:46 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

static int	numberlen(int num)
{
	int			len;
	long		n;

	n = num;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/**
 * @brief Converts an integer to a null-terminated string.
 *
 * Allocates memory for the string, including the sign if negative.
 *
 * @param n Integer to convert.
 * @return Pointer to the newly allocated string, or NULL on allocation failure.
 */
char	*ft_itoa(int n)
{
	int			len;
	char		*number;
	long		nbr;

	nbr = n;
	len = numberlen(nbr);
	number = malloc(sizeof(char) * (len + 1));
	if (!number)
		return (NULL);
	if (nbr == 0)
		number[0] = '0';
	if (nbr < 0)
	{
		number[0] = '-';
		nbr = -nbr;
	}
	number[len--] = '\0';
	while (len >= 0 && nbr > 0)
	{
		number[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (number);
}
