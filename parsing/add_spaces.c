/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:25:38 by pfreire-          #+#    #+#             */
/*   Updated: 2025/11/28 14:27:37 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	add_spaces_size_count(char *str)
{
	int		i;
	int		size;
	bool	inquote;
	bool	indquote;

	i = 0;
	size = 0;
	inquote = false;
	indquote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (str[i] == '<' || str[i] == '>')
		{
			if ((!indquote && !indquote) && (i > 0 && (str[i - 1] != ' '
						|| str[i - 1] != '>' || str[i - 1] != '<')))
				size++;
			if ((!indquote && !inquote) && (i > 0 && (str[i + 1] != ' ' || str[i
						+ 1] != '>' || str[i + 1] != '<')))
				size++;
		}
		i++;
		size++;
	}
	return (size);
}

char	**add_spaces(char *pipe)
{
	int		i;
	char	*dest;
	bool	indquote;
	bool	inquote;
	char	**final;
	int		j;

	i = 0;
	indquote = false;
	inquote = false;
	j = 0;
	dest = malloc(sizeof(char) * add_spaces_size_count(pipe) + 2);
	if (!dest)
		return (NULL);
	while (pipe[i])
	{
		if (pipe[i] == '\'' && !indquote)
			inquote = !inquote;
		if (pipe[i] == '\"' && !inquote)
			indquote = !indquote;
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
	final = split_ignore_quotes(dest, ' ', 0);
	free(dest);
	return (final);
}
