/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:48:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 14:51:37 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/parsing.h"

static t_redir *redir_new(t_redir_type redir_type, char *arg)
{
    t_redir *redir;

    redir = (t_redir *)calloc(1, sizeof(*redir));
    if (!redir)
        return NULL;
    redir->type = redir_type;
    if (redir_type == REDIR_HEREDOC)
        redir->delimiter = ft_strdup(arg);
    else
        redir->file = ft_strdup(arg);
    return redir;
}

int redir_append_cmd(t_cmd *cmd, t_redir_type redir_type, char *arg)
{
    t_redir *new_redir;
    t_redir *last;

    if (!cmd || !arg)
        return (1);
    new_redir = redir_new(redir_type, arg);
    if (!new_redir)
        return (1);
    if (!cmd->redirs)
    {
        cmd->redirs = new_redir;
        return (0);
    }
    last = cmd->redirs;
    while (last->next)
        last = last->next;
    last->next = new_redir;
    return (0);
}

bool is_redir(char *str)
{
    if (!str)
        return false;
    if (ft_strcmp(str, "<") == 0)
        return true;
    if (ft_strcmp(str, ">") == 0)
        return true;
    if (ft_strcmp(str, ">>") == 0)
        return true;
    if (ft_strcmp(str, "<<") == 0)
        return true;
    return false;
}
