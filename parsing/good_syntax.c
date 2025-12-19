/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:58:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/19 17:48:33 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static void	unexpected(char *str, int i)
{
	ft_printf("unexpected token near %c", str[i]);
	ft_printf("(coll: %d) nyan~\n", i);
}

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
		update_quote_state(str[i], &inquote, &indquote);
		if ((!inquote && !indquote) && str[i] == '|')
		{
			i++;
			i += count_whitespaces(str + i);
			if (str[i] == '|' || str[i] == '\0')
				return (unexpected(str, i), false);
		}
		i++;
	}
	return (true);
}

static int	helper(char *str, int i)
{
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
		i += count_whitespaces(str + i);
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '\0')
			return (ft_dprintf(2, "unexpected token near %c (coll:%d) nyan~\n",
					str[i - 1], i), 1);
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
			i++;
		i += count_whitespaces(str + i);
		if (str[i] == '|' || str[i] == '>' || str[i] == '<' || str[i] == '\0')
			return (ft_dprintf(2, "unexpected token near %c (coll:%d) nyan~\n",
					str[i], i), 1);
	}
	else if (str[i] == '\\' || str[i] == ';')
		return (1);
	return (0);
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
			if (helper(str, i))
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
