/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 12:14:51 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"
# include "../MiNyanShell.h"

// FIRST GENERAL EXECUTION FUNCTION (Mais coisas a adicionar)

void execute_command(t_subcmd *subcmd)
{
    char *cmd_path;

    cmd_path = get_command_path(subcmd->cmd);
    if (!cmd_path)
    {
        cmd_not_found_msg(subcmd->cmd);
        exit(127);
    }
    if (is_bultin(subcmd->cmd))
    {
        execute_builtin(subcmd);
        exit(0);
    }
    execve(cmd_path, subcmd->args, t_mini->env);



    
    
}
