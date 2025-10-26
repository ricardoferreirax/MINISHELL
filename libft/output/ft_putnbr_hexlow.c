/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexlow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:56:40 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:54:40 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

/**
 * @brief Prints an unsigned integer in lowercase hexadecimal to stdout.
 *
 * @param nb Unsigned integer to print.
 */
void	ft_putnbr_hexlow(unsigned int nb)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
		ft_putnbr_hexlow(nb / 16);
	ft_putchar(hex[nb % 16]);
}
