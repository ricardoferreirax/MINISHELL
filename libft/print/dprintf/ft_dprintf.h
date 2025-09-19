/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:22:44 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:16:03 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_dprinthex(int out, void *ptr, int *n);
void	ft_dputchar(int out, char c, int *n);
void	ft_dputnbr_hex(int out, unsigned int nb, int *n);
void	ft_dputnbr_hexlow(int out, unsigned int nb, int *n);
void	ft_dputnbr(int out, int nb, int *n);
void	ft_dputstr(int out, char *str, int *n);
void	ft_dputunbr(int out, unsigned int nb, int *n);
char	*ft_dstrlowcase(int out, char *str, int *n);
int		ft_dprintf(int out, const char *format, ...);

#endif
