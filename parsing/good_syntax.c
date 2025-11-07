/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:58:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/11/04 14:10:19 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	first_pipe(char *str)
{
	int	i;

	i = count_whitespaces(str);
	if (str[i] == '|')
		return (false);
	return (true);
}

bool	syntaxed_pipes(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	i = 0;
	inquote = false;
	indquote = false;
	if (!first_pipe(str))
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if ((!inquote && !indquote) && str[i] == '|')
		{
			i++;
			i += count_whitespaces(str + i);
			if (str[i] == '|' || str[i] == '\0')
				return (ft_printf("unexpected token near %c (coll: %d) nyan~\n",
						str[i], i), false);
		}
		i++;
	}
	return (true);
}

bool first_out(char *str)
{
	int i = count_whitespaces(str);
	if(str[i] == '>')
		return false;
	return true;
}

bool	unknown_action(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	i = 0;
	inquote = false;
	indquote = false;
	if(!first_out(str))
		return (ft_printf("Line Starts with redir out\n"), true);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (!indquote && !inquote)
		{
			if (str[i] == '>')
			{
				i++;
				if (str[i] == '>')
					i++;
				i += count_whitespaces(str + i);
				if (str[i] == '|' || str[i] == '<' || str[i] == '>'
					|| str[i] == '\0')
					return (ft_dprintf(2, "unexpected token near %c (coll:%d) nyan~\n", str[i - 1], i), true);
			}
			else if (str[i] == '<')
			{
				i++;
				if (str[i] == '<')
					i++;
				i += count_whitespaces(str + i);
				if (str[i] == '|' || str[i] == '>' || str[i] == '<'
					|| str[i] == '\0')
					return (ft_dprintf(2, "unexpected token near %c (coll:%d) nyan~\n", str[i], i), true);
			}
			else if (str[i] == '\\' || str[i] == ';')
				return (true);
		}
		i++;
	}
	return (false);
}

bool	good_syntax(char *input)
{
	if (!syntaxed_pipes(input))
		return ( false);
	if (unknown_action(input))
		return (false);
	return (true);
}
