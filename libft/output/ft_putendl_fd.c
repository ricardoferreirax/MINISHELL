/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:30:23 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:54:40 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

/**

 * @brief Prints a string followed by a newline to the specified file descriptor.
 *
 * Does nothing if the string is NULL.
 *
 * @param s String to print.
 * @param fd File descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
