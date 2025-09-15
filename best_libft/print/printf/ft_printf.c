/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:26:25 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:59:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_case(char a, va_list *arg, int *n)
{
	if (a == 'c')
		ft_putlchar(va_arg(*arg, int), n);
	else if (a == 's')
		ft_putlstr(va_arg(*arg, char *), n);
	else if (a == 'p')
		ft_printlhex(va_arg(*arg, void *), n);
	else if (a == 'd')
		ft_putlnbr(va_arg(*arg, int), n);
	else if (a == 'i')
		ft_putlnbr(va_arg(*arg, int), n);
	else if (a == 'u')
		ft_putlunbr(va_arg(*arg, unsigned int), n);
	else if (a == 'x')
		ft_putlnbr_hexlow(va_arg(*arg, unsigned int), n);
	else if (a == 'X')
		ft_putlnbr_hex(va_arg(*arg, unsigned int), n);
	else if (a == '%')
		ft_putlchar('%', n);
}

/// @brief Prints string to standard output
/// @param format string
/// @param %c for a single char, %s for string, 
//  %p for an adress in hex,
//	%d for decimal number, 
//	%i for integer in base 10, 
//  %u for an unsigned interger. 
//	%x for lowercas hexadecimal number,
//	%X for upercase hexadicimal number
/// @return
int	ft_printf(const char *format, ...)
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
			ft_case(format[i + 1], &args, &char_nbr);
			i += 2;
			continue ;
		}
		ft_putlchar(format[i], &char_nbr);
		i++;
	}
	va_end(args);
	return (char_nbr);
}
