/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:18:49 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:34:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputnbr_hex(int out, unsigned int nb, int *n)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (nb >= 16)
		ft_dputnbr_hex(out, nb / 16, n);
	ft_dputchar(out, hex[nb % 16], n);
}
// int main()
// {
// 	int i;

// 	i = 0;
// 	while (i < 100)
// 	{
// 		ft_putnbr_hex(i, &i);
// 		printf("\n");
// 		i++;
// 	}
// }