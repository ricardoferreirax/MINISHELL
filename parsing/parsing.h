/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:29 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/16 14:23:01 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

# include "../libft/libft.h"

// AUX Funcs
int	count_words_ignore_quotes(char *str, char c);
char	*word_copy_ignorequotes(char **s, char c);
char	**split_ignore_quotes(char *str, char c);
char	**ft_split_quotes(char const *s, char c);


#endif