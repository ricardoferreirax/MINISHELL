/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:52:15 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:10:58 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "unistd.h"

void	ft_printhex(void *ptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_hex(unsigned int nb);
void	ft_putnbr_hexlow(unsigned int nb);
void	ft_putnbr(int nb);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *str);
void	ft_putunbr(unsigned int nb);

#endif
