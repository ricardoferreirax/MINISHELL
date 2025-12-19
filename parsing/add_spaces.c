/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:25:38 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/18 20:41:52 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	add_spaces_size_count(char *str)
{
	int		i;
	int		size;
	bool	inquote;
	bool	indquote;

	i = -1;
	size = 0;
	inquote = false;
	indquote = false;
	while (str[++i] != '\0')
	{
		update_quote_state(str[i], &inquote, &indquote);
		if (str[i] == '<' || str[i] == '>')
		{
			if ((!indquote && !indquote) && (i > 0 && (str[i - 1] != ' '
						|| str[i - 1] != '>' || str[i - 1] != '<')))
				size++;
			if ((!indquote && !inquote) && (i > 0 && (str[i + 1] != ' ' || str[i
						+ 1] != '>' || str[i + 1] != '<')))
				size++;
		}
		size++;
	}
	return (size);
}

static void	helper(char *pipe, char *dest)
{
	int		i;
	int		j;
	bool	inquote;
	bool	indquote;

	i = 0;
	j = 0;
	inquote = false;
	indquote = false;
	while (pipe[i])
	{
		update_quote_state(pipe[i], &inquote, &indquote);
		if (pipe[i] == '<' || pipe[i] == '>')
		{
			if ((!inquote && !indquote) && (i > 0 && (pipe[i - 1] != ' '
						&& pipe[i - 1] != '>' && pipe[i - 1] != '<')))
			{
				dest[j + i] = ' ';
				j++;
			}
			dest[j + i] = pipe[i];
			i++;
			if ((!inquote && !indquote) && (pipe[i] != ' ' && pipe[i] != '>'
					&& pipe[i] != '<'))
			{
				dest[j + i] = ' ';
				j++;
			}
			continue ;
		}
		dest[i + j] = pipe[i];
		i++;
	}
	dest[i + j] = '\0';
	dest[i + j + 1] = '\0';
}

char	**add_spaces(char *pipe)
{
	char	*dest;
	char	**final;

	dest = malloc(sizeof(char) * add_spaces_size_count(pipe) + 2);
	if (!dest)
		return (NULL);
	helper(pipe, dest);
	final = split_ignore_quotes(dest, ' ', 0);
	free(dest);
	return (final);
}
