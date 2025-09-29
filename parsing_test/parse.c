/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:24:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 16:07:21 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/parsing.h"

/* devolve 1 se consumiu algo com sucesso, 0 se erro de sintaxe */
int	parse(t_subcmd *sub, char **tokens, int *i)
{
	char	*op;

	if (tokens[*i] && !is_redir(tokens[*i]))
	{
		if (!sub->cmd)
		{
			sub->cmd = ft_strdup(tokens[*i]);
			if (!sub->cmd)
				return (0);
		}
		while (tokens[*i] && !is_redir(tokens[*i]))
		{
			if (add_arg(sub, tokens[*i]) != 0)
				return (0);
			(*i)++;
		}
		return (1);
	}
	if (tokens[*i] && is_redir(tokens[*i]))
	{
		op = tokens[*i];
		(*i)++;
		if (!tokens[*i] || is_redir(tokens[*i]))
			return (0); /* operador sem alvo */
		if (ft_strcmp(op, "<<") == 0)
		{
			if (redir_append(sub, REDIR_HEREDOC, tokens[*i]) != 0)
				return (0);
		}
		else if (ft_strcmp(op, "<") == 0)
		{
			if (redir_append(sub, REDIR_IN, tokens[*i]) != 0)
				return (0);
		}
		else if (ft_strcmp(op, ">>") == 0)
		{
			if (redir_append(sub, REDIR_APPEND, tokens[*i]) != 0)
				return (0);
		}
		else if (ft_strcmp(op, ">") == 0)
		{
			if (redir_append(sub, REDIR_OUT, tokens[*i]) != 0)
				return (0);
		}
		(*i)++;
		return (1);
	}
	return (0);
}
