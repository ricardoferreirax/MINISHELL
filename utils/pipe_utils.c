/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:utils/pipe_utils.c
/*   Created: 2025/09/16 15:11:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 12:15:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	safe_dup2_and_close(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (0);
	if (dup2(oldfd, newfd) == -1)
	{
		perror("minishell: dup2 error");
		close(oldfd);
		return (1);
	}
	close(oldfd);
	return (0);
}
=======
/*   Created: 2025/09/16 09:52:29 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/22 14:00:33 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"

// AUX Funcs
int		count_words_ignore_quotes(char *str, char c);
char	*word_copy_ignorequotes(char **s, char c);
char	**split_ignore_quotes(char *str, char c);
char	**ft_split_quotes(char const *s, char c);
bool	no_unclosed_quotes(char *str);
#endif
>>>>>>> pedro:parsing/parsing.h
