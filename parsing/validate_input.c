/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:46:47 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 14:51:53 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool no_forbidden_actions(char *str)
{
    int  i;
    bool in_squote;
    bool in_dquote;

    if (!str)
        return true;
    i = 0;
    in_squote = false;
    in_dquote = false;
    while (str[i] != '\0')
    {
        if (str[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (str[i] == '\"' && !in_squote)
            in_dquote = !in_dquote;
        if (!in_squote && !in_dquote)
        {
            if (str[i] == '&' && str[i + 1] == '&')
                return false;
            if (str[i] == '|' && str[i + 1] == '|')
                return false;
        }
        i++;
    }
    return true;
}

bool no_unclosed_quotes(char *str)
{
    bool in_squote;
    bool in_dquote;
    int  i;

    in_squote = false;
    in_dquote = false;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        if (str[i] == '\"' && !in_squote)
            in_dquote = !in_dquote;
        i++;
    }
    if (in_dquote || in_squote)
        return false;
    return true;
}
