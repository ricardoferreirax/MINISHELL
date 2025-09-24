/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:04:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/24 22:09:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

int     ft_strcmp(char *s1, char *s2);
size_t  ft_strlen(const char *s);
void    ft_putstr_fd(char *s, int fd);
char  **ft_split_quotes(char const *s, char c);

#endif
