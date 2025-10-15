/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:43:29 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 14:50:48 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/envyan.h"

static void print_env_list(t_envyan *head)
{
    t_envyan *current;

    current = head;
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
}

int ft_env(t_cmd *cmd, t_mini *mini)
{
    if (!mini)
        return (1);
    if (!cmd || !cmd->args || !cmd->args[1])   // sem argumentos imprimimos o env
    {
        print_env_list(mini->envyan);
        mini->last_status = 0;
        return (0);
    }
    ft_putstr_fd("env: ‘", STDERR_FILENO);
    ft_putstr_fd(cmd->args[1], STDERR_FILENO);
    ft_putendl_fd("’: No such file or directory", STDERR_FILENO);
    mini->last_status = 127;
    return (127);
}
