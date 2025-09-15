/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr_hexlow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:17 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:34:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputnbr_hexlow(int out, unsigned int nb, int *n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
		ft_dputnbr_hexlow(out, nb / 16, n);
	ft_dputchar(out, hex[nb % 16], n);
}
