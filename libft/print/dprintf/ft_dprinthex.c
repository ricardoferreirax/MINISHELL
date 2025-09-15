/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprinthex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:21:17 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:35:45 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	ft_dputnbr_hexadrs(int out, unsigned long nb, int *n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
		ft_dputnbr_hexadrs(out, nb / 16, n);
	ft_dputchar(out, hex[nb % 16], n);
}

void	ft_dprinthex(int out, void *ptr, int *n)
{
	unsigned long	i;

	i = (unsigned long)ptr;
	if (ptr == NULL)
	{
		ft_dputstr(out, "(nil)", n);
		return ;
	}
	ft_dputchar(out, '0', n);
	ft_dputchar(out, 'x', n);
	ft_dputnbr_hexadrs(out, i, n);
}
