/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:51:23 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/16 16:32:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

void cleanup_iteration(t_mini *mini)
{
    if (!mini)
        return ;
    if (mini->head)
        free_cmd_list(&mini->head);
}

void minyanshell_exit_cleanup(t_mini *mini)
{
    if (!mini)
        return ;
    if (mini->head)
        free_cmd_list(&mini->head);
    if (mini->envyan)
        free_envyan(&mini->envyan);
    rl_clear_history();
	close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void minyanshell_child_cleanup_and_exit(t_mini *mini, int status)
{
    if (mini)
    {
        if (mini->head)
            free_cmd_list(&mini->head);
        if (mini->envyan)
            free_envyan(&mini->envyan);
    }
    exit(status);
}
