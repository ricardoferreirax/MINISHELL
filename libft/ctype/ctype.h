/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctype.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:34:57 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:01:25 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTYPE_H
# define CTYPE_H

int	ft_isalnum(char a);
int	ft_isalpha(int a);
int	ft_isascii(int a);
int	ft_isblank(int c);
int	ft_iscntrl(int c);
int	ft_isdigit(int i);
int	ft_isgraph(int c);
int	ft_islower(int c);
int	ft_isprint(int a);
int	ft_ispunct(int c);
int	ft_isspace(int c);
int	ft_isupper(int c);
int	ft_isxdigit(int c);
int	ft_tolower(int a);
int	ft_toupper(int a);

#endif
