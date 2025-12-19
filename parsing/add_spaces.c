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

static void	helper(char *p, char *dest)
{
	int		i[2];
	bool	q[2];

	i[0] = 0;
	i[1] = 0;
	q[0] = false;
	q[1] = false;
	while (p[i[0]])
	{
		update_quote_state(p[i[0]], &q[0], &q[1]);
		if (p[i[0]] == '<' || p[i[0]] == '>')
		{
			if ((!q[0] && !q[1]) && (i[0] > 0 && (p[i[0] - 1] != ' ' && p[i[0]
							- 1] != '>' && p[i[0] - 1] != '<')))
				dest[i[1]++ + i[0]] = ' ';
			dest[i[1] + i[0]] = p[i[0]];
			i[0]++;
			if ((!q[0] && !q[1]) && (p[i[0]] != ' ' && p[i[0]] != '>'
					&& p[i[0]] != '<'))
				dest[i[1]++ + i[0]] = ' ';
			continue ;
		}
		dest[i[0] + i[1]] = p[i[0]];
		i[0]++;
	}
}

char	**add_spaces(char *pipe)
{
	char	*dest;
	char	**final;

	dest = ft_calloc(sizeof(char), add_spaces_size_count(pipe) + 2);
	if (!dest)
		return (NULL);
	helper(pipe, dest);
	final = split_ignore_quotes(dest, ' ', 0);
	free(dest);
	return (final);
}
