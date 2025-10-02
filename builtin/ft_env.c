/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:22:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/01 16:44:19 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static int env_check_args(t_mini *mini, t_subcmd *subcmd)
{
    if (subcmd && subcmd->args && subcmd->args[1])
    {
        write(STDERR_FILENO, "env: ", 5);
        write(STDERR_FILENO, subcmd->args[1], ft_strlen(subcmd->args[1]));
        write(STDERR_FILENO, ": No such file or directory\n", 29);
        if (mini) 
            mini->last_status = 127;
        return (127);
    }
    return 0;
}

int ft_env(t_mini *mini, t_subcmd *subcmd)
{
    int i;
    int check;

    check = env_check_args(mini, subcmd);
    if (check != 0)
        return (check);
    if (!mini || !mini->env)
    {
        if (mini) mini->last_status = 0;
        return (0);
    }
    i = 0;
    while (mini->env[i])
    {
        if (ft_strchr(mini->env[i], '='))
        {
            write(STDOUT_FILENO, mini->env[i], ft_strlen(mini->env[i]));
            write(STDOUT_FILENO, "\n", 1);
        }
        i++;
    }
    mini->last_status = 0;
    return (0);
}

