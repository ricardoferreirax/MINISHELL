/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputunbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:18:49 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:34:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputunbr(int out, unsigned int nb, int *n)
{
	if (nb >= 10)
	{
		ft_dputunbr(out, nb / 10, n);
		ft_dputunbr(out, nb % 10, n);
	}
	if (nb < 10)
	{
		ft_dputchar(out, nb + '0', n);
	}
}
