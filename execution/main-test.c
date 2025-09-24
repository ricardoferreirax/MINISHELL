/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:55:09 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/24 22:13:06 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../MiNyanShell.h"

void	init_subcmd(t_subcmd *subcmd)
{
	if (!subcmd)
		return;
	subcmd->type = REDIR_INVALID;
	subcmd->delimiter = NULL;
	subcmd->args = NULL;
	subcmd->cmd = NULL;
	subcmd->infile = NULL;
	subcmd->outfile = NULL;
	subcmd->next = NULL;
	subcmd->redirs = NULL;
	subcmd->cmd_type = NONE_CMD;
	subcmd->in_fd = -1;
	subcmd->out_fd = -1;
}

void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	cmd->head = NULL;
	cmd->next = NULL;
}

void	init_mini(t_mini *mini, char **envp)
{
	if (!mini)
		return;
	mini->head = NULL;
	mini->last_status = 0;
	mini->env = envp;
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_mini  shell;

    (void)argc;
    (void)argv;
    init_mini(&shell, envp);
    while (1)
    {
        input = readline("minishell$ ");
        if (!input) // CTRL+D
        {
            printf("exit\n");
            break;
        }
        printf("[DEBUG]: %s\n", input);
        execute_commands(&shell);
    }
    return (0);
}