/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:21:17 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:59:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putlnbr_hexadrs(unsigned long nb, int *n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
		ft_putlnbr_hexadrs(nb / 16, n);
	ft_putlchar(hex[nb % 16], n);
}

/// @brief Prints the hexadecimal adress of the pointer
//	and counts the number of chars printed
/// @param ptr pointer
/// @param n adress of the counter
void	ft_printlhex(void *ptr, int *n)
{
	unsigned long	i;

	i = (unsigned long)ptr;
	if (ptr == NULL)
	{
		ft_putlstr("(nil)", n);
		return ;
	}
	ft_putlchar('0', n);
	ft_putlchar('x', n);
	ft_putlnbr_hexadrs(i, n);
}
