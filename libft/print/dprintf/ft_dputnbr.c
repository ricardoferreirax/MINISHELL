/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:18:49 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:34:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputnbr(int out, int nb, int *n)
{
	if (nb == -2147483648)
	{
		ft_dputstr(out, "-2147483648", n);
		return ;
	}
	if (nb < 0)
	{
		ft_dputchar(out, '-', n);
		nb = nb * -1;
	}
	if (nb >= 10)
		ft_dputnbr(out, nb / 10, n);
	ft_dputchar(out, (nb % 10) + '0', n);
}
