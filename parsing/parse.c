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

//for this to return true str must be double '\0' terminated and also be equal to base
int sneaky_strcmp(char *str, char *base)
{
	int i = 0;
	while(base[i] != '\0' && str[i] != '\0' && (base[i] == str[i]))
		i++;
	if(base[i] == '\0' && str[i] == '\0')
	{
		if(str[i + 1] == '\0')
			return 1;
	}
	return 0;
}

bool is_redir(char *str)
{
    if (!str)
        return false;
    if (sneaky_strcmp(str, "<"))
        return true;
    if (sneaky_strcmp(str, ">"))
        return true;
    if (sneaky_strcmp(str, ">>"))
        return true;
    if (sneaky_strcmp(str, "<<"))
        return true;
    return false;
}

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
        if (sneaky_strcmp(op, "<<"))
        {
            if (redir_append(cmd, REDIR_HEREDOC, tokens[*i]) != 0)
                return (0);
        }
        else if (sneaky_strcmp(op, "<"))
        {
            if (redir_append(cmd, REDIR_IN, tokens[*i]) != 0)
                return (0);
        }
        else if (sneaky_strcmp(op, ">>"))
        {
            if (redir_append(cmd, REDIR_APPEND, tokens[*i]) != 0)
                return (0);
        }
        else if (sneaky_strcmp(op, ">"))
        {
            if (redir_append(cmd, REDIR_OUT, tokens[*i]) != 0)
                return (0);
        }
        (*i)++;
        return (1);
    }
    return (0);
}
