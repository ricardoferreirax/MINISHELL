/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:24:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/04 14:10:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	sneaky_strcmp(char *str, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0' && str[i] != '\0' && (base[i] == str[i]))
		i++;
	if (base[i] == '\0' && str[i] == '\0')
	{
		if (str[i + 1] == '\0')
			return (1);
	}
	return (0);
}

bool	is_redir(char *str)
{
	if (!str)
		return (false);
	if (ft_strcmp(str, "<"))
		return (true);
	if (ft_strcmp(str, ">"))
		return (true);
	if (ft_strcmp(str, ">>"))
		return (true);
	if (ft_strcmp(str, "<<"))
		return (true);
	return (false);
}

bool	sneaky_is_redir(char *str)
{
	if (!str)
		return (false);
	if (sneaky_strcmp(str, "<"))
		return (true);
	if (sneaky_strcmp(str, ">"))
		return (true);
	if (sneaky_strcmp(str, ">>"))
		return (true);
	if (sneaky_strcmp(str, "<<"))
		return (true);
	return (false);
}

static int	helper(t_cmd *cmd, char *op, char *tokens)
{
	if (sneaky_strcmp(op, "<<") && (redir_append(cmd, REDIR_HEREDOC,
				tokens) != 0))
		return (-1);
	else if (sneaky_strcmp(op, "<") && (redir_append(cmd, REDIR_IN,
				tokens) != 0))
		return (-1);
	else if (sneaky_strcmp(op, ">>") && (redir_append(cmd, REDIR_APPEND,
				tokens) != 0))
		return (-1);
	else if (sneaky_strcmp(op, ">") && (redir_append(cmd, REDIR_OUT,
				tokens) != 0))
		return (-1);
	return (0);
}

int	parse(t_cmd *cmd, char **tokens, int *i)
{
	char	*op;

	if (!tokens[*i])
		return (0);
	if (!sneaky_is_redir(tokens[*i]))
	{
		while (tokens[*i] && !sneaky_is_redir(tokens[*i]))
		{
			if (add_arg(cmd, tokens[*i]) != 0)
				return (-1);
			(*i)++;
		}
		return (0);
	}
	op = tokens[(*i)++];
	if (!tokens[*i] || sneaky_is_redir(tokens[*i]))
		return (-1);
	if (helper(cmd, op, tokens[*i]))
		return (-1);
	(*i)++;
	return (0);
}
