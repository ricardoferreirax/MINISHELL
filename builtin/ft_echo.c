/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:04:13 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 00:26:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/builtin.h"

static int is_valid_n_case(char **args)
{
    int i;
    int j;

    i = 1;
    while (args && args[i])
    {
        j = 0;
        if (args[i][j] == '-')
        {
            j++;
            if (args[i][j] != 'n')
                break;
            while (args[i][j] == 'n')
                j++;
            if (args[i][j] != '\0')
                break;
        }
        else
            break;
        i++;
    }
    return (i);
}

int ft_echo(t_cmd *cmd)
{
    int i;
    int n_index;

    if (!cmd || !cmd->cmd_args)
        return (0);
    i = is_valid_n_case(cmd->cmd_args);
    n_index = i;
    if (cmd->cmd_args[i])
    {
        while (cmd->cmd_args[i])
        {
            write(STDOUT_FILENO, cmd->cmd_args[i], ft_strlen(cmd->cmd_args[i]));
            if (cmd->cmd_args[i + 1])
                write(STDOUT_FILENO, " ", 1);
            i++;
        }
        if (n_index == 1)
            write(STDOUT_FILENO, "\n", 1);
    }
    else if (n_index == 1)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
