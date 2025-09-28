/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:19:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 00:03:23 by rmedeiro         ###   ########.fr       */
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

static void free_cmd_list(t_cmd *cmd) 
{
    t_cmd *c = cmd;
    while (c) 
    {
        t_subcmd *s = c->head;
        while (s) 
        {
            if (s->in_fd != -1)
                close(s->in_fd);
            t_subcmd *sn = s->next;
            free(s);
            s = sn;
        }
        t_cmd *cn = c->next;
        free(c);
        c = cn;
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc; 
    (void)argv;

    t_mini  mini;
    char    *input;
    char    **pipes;
    int     status;
    
    mini.head = NULL;
    mini.env = envp;
    mini.last_status = 0;
    
    while (1)
    {
        input = readline("minishell> ");
        if (!input) 
        {                 /* Ctrl+D */
            printf("exit\n");
            break;
        }
        if (*input) 
            add_history(input);
        if (!no_unclosed_quotes(input))
        {
            fprintf(stderr, "MiNyanShell: syntax error: unclosed quotes\n");
            free(input);
            continue;
        }
        if (!no_forbidden_actions(input))
        {
            fprintf(stderr, "MiNyanShell: unsupported operator (&&, ||, *)\n");
            free(input);
            continue;
        }
        pipes = init_mini(&mini, input);
        if (!pipes)
        {
            perror("init_mini");
            free(input);
            continue;
        }
        fill_mini(&mini, pipes);
        free_2d((void **)pipes);
        status = ft_execution(mini.head, &mini);
        mini.last_status = status;
        free_cmd_list(mini.head);
        mini.head = NULL;

        free(input);
    }
    return (0);
}