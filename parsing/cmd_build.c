/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:56:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 19:48:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "../include/parsing.h"

t_cmd *cmd_new(void)
{
    t_cmd *cmd;

    cmd = (t_cmd *)calloc(1, sizeof(*cmd));
    if (!cmd)
        return NULL;
    cmd->cmd_args = NULL;
    cmd->redirs   = NULL;
    cmd->in_fd    = -1;
    cmd->next     = NULL;
    return cmd;
}

int add_arg_cmd(t_cmd *cmd, const char *token)
{
    int   count;
    int   i;
    char **new_arg;

    if (!cmd || !token)
        return (1);
    count = 0;
    if (cmd->cmd_args)
    {
        while (cmd->cmd_args[count])
            count++;
    }
    new_arg = (char **)malloc((count + 2) * sizeof(char *));
    if (!new_arg)
        return (1);
    i = 0;
    while (i < count)
    {
        new_arg[i] = cmd->cmd_args[i];
        i++;
    }
    new_arg[count] = ft_strdup(token);
    if (!new_arg[count])
    {
        free(new_arg);
        return (1);
    }
    new_arg[count + 1] = NULL;
    if (cmd->cmd_args)
        free(cmd->cmd_args);
    cmd->cmd_args = new_arg;
    return (0);
}
