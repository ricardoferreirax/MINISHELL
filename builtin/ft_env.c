/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:43:29 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 00:45:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/builtin.h"
#include "../include/envyan.h"

int ft_env(t_cmd *cmd, t_mini *mini)
{
    t_envyan *current;

    if (!mini)
        return (1);
    if (cmd && cmd->cmd_args && cmd->cmd_args[1])
    {
        ft_putstr_fd("MiNyanShell: env: too many arguments\n", STDERR_FILENO);
        mini->last_status = 1;
        return (1);
    }
    current = mini->envyan;
    while (current)
    {
        if (current->value != NULL)
        {
            ft_putstr_fd(current->key, STDOUT_FILENO);
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putendl_fd(current->value, STDOUT_FILENO);
        }
        current = current->next;
    }
    mini->last_status = 0;
    return (0);
}
