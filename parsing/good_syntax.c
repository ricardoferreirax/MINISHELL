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

bool	syntaxed_pipes(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	i = 0;
	inquote = false;
	indquote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if ((!inquote && !indquote) && str[i] == '|')
		{
			i++;
			while (str[i] <= 9 || str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (ft_printf("unexpected token near %c (coll: %d) nyan~\n",
						str[i], i), false);
		}
		i++;
	}
	return (true);
}

bool	unknown_action(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	i = 0;
	inquote = false;
	indquote = false;
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
				while ((str[i] <= 9 || str[i] == ' ') && str[i] != '\0')
					i++;
				if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '\0')
					return (ft_dprintf(2, "unexpected token near %c (coll: %d) nyan~\n", str[i - 1], i), true);
			}
			else if (str[i] == '<')
			{
				i++;
				if (str[i] == '<')
					i++;
				while ((str[i] <= 9 || str[i] == ' ') && str[i] != '\0')
					i++;
				if (str[i] == '|' || str[i] == '>' || str[i] == '<' || str[i] == '\0')
					return (ft_dprintf(2, "unexpected token near %c (coll: %d) nyan~\n", str[i], i), true);
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
		return (false);
	if (unknown_action(input))
		return (false);
	return (true);
}
