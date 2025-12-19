/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:17 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:15:57 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "stdarg.h"
# include "unistd.h"

int		ft_printf(const char *format, ...);
void	ft_case(char a, va_list *arg, int *n);
void	ft_printlhex(void *ptr, int *n);
void	ft_putlchar(char c, int *n);
void	ft_putlnbr_hex(unsigned int nb, int *n);
void	ft_putlnbr_hexlow(unsigned int nb, int *n);
void	ft_putlnbr(int nb, int *n);
void	ft_putlstr(char *str, int *n);
void	ft_putlunbr(unsigned int nb, int *n);

#endif
