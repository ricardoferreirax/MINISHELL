/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:33:29 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:54:40 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

/**
 * @brief Prints an integer to the specified file descriptor.
 *
 * Handles negative numbers and the minimum integer value.
 *
 * @param n Integer to print.
 * @param fd File descriptor to write to.
 */
void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	if (nb < 10)
	{
		ft_putchar_fd(nb + '0', fd);
	}
}
