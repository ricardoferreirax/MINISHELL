/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:26:25 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:35:15 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dcase(int out, char a, va_list *arg, int *n)
{
	if (a == 'c')
		ft_dputchar(out, va_arg(*arg, int), n);
	else if (a == 's')
		ft_dputstr(out, va_arg(*arg, char *), n);
	else if (a == 'p')
		ft_dprinthex(out, va_arg(*arg, void *), n);
	else if (a == 'd')
		ft_dputnbr(out, va_arg(*arg, int), n);
	else if (a == 'i')
		ft_dputnbr(out, va_arg(*arg, int), n);
	else if (a == 'u')
		ft_dputunbr(out, va_arg(*arg, unsigned int), n);
	else if (a == 'x')
		ft_dputnbr_hexlow(out, va_arg(*arg, unsigned int), n);
	else if (a == 'X')
		ft_dputnbr_hex(out, va_arg(*arg, unsigned int), n);
	else if (a == '%')
		ft_dputchar(out, '%', n);
}

/**
 * @brief Mimics the standard dprintf function,
	writing formatted output to the given file descriptor.
 *
 * Supports the same format specifiers as ft_printf: characters, strings,
	integers,
 * unsigned integers, hexadecimal (uppercase and lowercase), pointers,
	and percent.
 *
 * Example usage:
 * @code
 * int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
 * ft_dprintf(fd, "Error code: %d\n", err);
 * close(fd);
 * @endcode
 *
 * @param fd File descriptor where the output should be written.

 * @param format Format string containing literal characters and format
 specifiers.
 * @param ... Arguments corresponding to the format specifiers.
 * @return The total number of characters written, excluding the null byte.
 */
int	ft_dprintf(int out, const char *format, ...)
{
	va_list	args;
	int		i;
	int		char_nbr;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	char_nbr = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			ft_dcase(out, format[i + 1], &args, &char_nbr);
			i += 2;
			continue ;
		}
		ft_dputchar(out, format[i], &char_nbr);
		i++;
	}
	va_end(args);
	return (char_nbr);
}
