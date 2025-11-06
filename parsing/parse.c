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

int parse(t_cmd *cmd, char **tokens, int *i)
{
    char *op;

    if (tokens[*i] && !is_redir(tokens[*i]))
    {
        while (tokens[*i] && !is_redir(tokens[*i]))
        {
            if (add_arg(cmd, tokens[*i]) != 0)
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
            return (0);
        if (ft_strcmp(op, "<<") == 0)
        {
            if (redir_append(cmd, REDIR_HEREDOC, tokens[*i]) != 0)
                return (0);
        }
        else if (ft_strcmp(op, "<") == 0)
        {
            if (redir_append(cmd, REDIR_IN, tokens[*i]) != 0)
                return (0);
        }
        else if (ft_strcmp(op, ">>") == 0)
        {
            if (redir_append(cmd, REDIR_APPEND, tokens[*i]) != 0)
                return (0);
        }
        else if (ft_strcmp(op, ">") == 0)
        {
            if (redir_append(cmd, REDIR_OUT, tokens[*i]) != 0)
                return (0);
        }
        (*i)++;
        return (1);
    }
    return (0);
}
