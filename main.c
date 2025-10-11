/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:18:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/11 12:51:31 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/parsing.h"
#include "../include/envyan.h"

static void process_line(t_mini *mini, char *input)
{
    char  **pipes;
    int     status;

    if (!input || !mini)
        return;
    if (*input)
        add_history(input);
    if (!no_unclosed_quotes(input))
    {
        ft_dprintf(2, "MiNyanShell: syntax error: unclosed quotes\n");
        return ;
    }
    if (!no_forbidden_actions(input))
    {
        ft_dprintf(2, "MiNyanShell: unsupported operator (&&, ||, *)\n");
        return ;
    }
    pipes = init_mini(mini, input);
    if (!pipes)
    {
        perror("init_mini");
        return ;
    }
    fill_mini(mini, pipes);
    free_2d((void **)pipes);
    status = execute_pipeline(mini->head, mini);
    mini->last_status = status;
    free_cmd_list(mini->head);
    mini->head = NULL;
}

static void command_loop(t_mini *mini)
{
    char *input;

    while (1)
    {
        input = readline("MiNyanShell> ");
        if (!input)
        {
            printf("\nexit\n");
            break;
        }
        if (input[0] != '\0')
            process_line(mini, input);
        free(input);
    }
}

static void init_shell(t_mini *mini, char **envp)
{
    t_envyan *last_node;
    int shlvl;

    if (!mini)
        return ;
    mini->head = NULL;
    mini->envyan = init_envyan(envp);
    last_node = get_last_envyan(mini->envyan);
    shlvl = get_shlvl_from_envp(envp);
    mini->envyan = process_shlvl(&mini->envyan, &last_node, shlvl);
    mini->last_status = 0;
    /* set_interactive_signals(); */
}

int main(int ac, char **av, char **envp)
{
    t_mini mini;

    if (ac != 1)
    {
        if (av && av[1])
            ft_dprintf(2, "MiNyanShell: %s: Invalid argument\n", av[1]);
        else
            ft_dprintf(2, "MiNyanShell: Invalid argument\n");
        return (1);
    }
    init_shell(&mini, envp);
    command_loop(&mini);
    rl_clear_history();
    free_envyan(mini.envyan);
    return (mini.last_status);
}
