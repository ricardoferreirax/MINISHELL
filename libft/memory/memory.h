/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:47:13 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:10:53 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "stdint.h"
# include "stdlib.h"
# include "unistd.h"
# include <string.h>

void	ft_bzero(void *a, size_t i);
void	*ft_calloc(size_t nmemb, size_t size);
void	free_chararr(char **array);
void	*ft_memchr(const void *a, int b, size_t c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t i);
void	*ft_memmove(void *dest, const void *src, size_t i);
void	*ft_memset(void *a, int c, size_t i);

#endif