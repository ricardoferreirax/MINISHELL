/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:29 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/22 11:55:51 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define NULL ((void)*)
# include "../libft/libft.h"

// AUX Funcs
int		count_words_ignore_quotes(char *str, char c);
char	*word_copy_ignorequotes(char **s, char c);
char	**split_ignore_quotes(char *str, char c);
char	**ft_split_quotes(char const *s, char c);
bool	no_unclosed_quotes(char *str);
#endif