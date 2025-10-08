/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:43:29 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:45:40 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/envyan.h"

static void print_env_list(t_envyan *head)
{
    t_envyan *cur;

    cur = head;
    while (cur)
    {
        if (cur->value != NULL)
        {
            ft_putstr_fd(cur->key, STDOUT_FILENO);
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putendl_fd(cur->value, STDOUT_FILENO);
        }
        cur = cur->next;
    }
}

int ft_env(t_cmd *cmd, t_mini *mini)
{
    t_cmd sub;
    int   status;

    if (!mini)
        return (1);
    if (!cmd || !cmd->args || !cmd->args[1])
    {
        print_env_list(mini->envyan);
        mini->last_status = 0;
        return (0);
    }
    sub = *cmd;
    sub.args = &cmd->args[1];
    status = execute_single_cmd(&sub, mini);
    if (status == NOT_BUILTIN)
        status = execute_external_cmd(&sub, mini);
    mini->last_status = status;
    return (status);
}
