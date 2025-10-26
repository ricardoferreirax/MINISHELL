/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:49:44 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:52:56 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

static void	ft_putnbr_hexadrs(unsigned long nb)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
		ft_putnbr_hexadrs(nb / 16);
	ft_putchar(hex[nb % 16]);
}

/**
 * @brief Prints the hexadecimal address of a pointer to stdout.
 *
 * Prints "(nil)" if the pointer is NULL.
 *
 * @param ptr Pointer to print.
 */
void	ft_printhex(void *ptr)
{
	unsigned long	i;

	i = (unsigned long)ptr;
	if (ptr == NULL)
	{
		ft_putstr("(nil)");
		return ;
	}
	ft_putchar('0');
	ft_putchar('x');
	ft_putnbr_hexadrs(i);
}
