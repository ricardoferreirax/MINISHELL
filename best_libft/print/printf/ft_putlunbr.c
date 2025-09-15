/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlunbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:18:49 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:59:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putlunbr(unsigned int nb, int *n)
{
	if (nb >= 10)
	{
		ft_putlunbr(nb / 10, n);
		ft_putlunbr(nb % 10, n);
	}
	if (nb < 10)
	{
		ft_putlchar(nb + '0', n);
	}
}
