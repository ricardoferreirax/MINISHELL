/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:19:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/28 18:45:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/MiNyanShell.h"
#include "../include/execution.h"

static t_subcmd *new_subcmd(char **args) 
{
    t_subcmd *s = calloc(1, sizeof(*s));
    if (!s) 
        return NULL;
    s->args = args;
    s->redirs = NULL;
    s->in_fd = -1;
    s->next = NULL;
    return s;
}
static t_cmd *new_cmd_with_subcmd(t_subcmd *sub) 
{
    t_cmd *c = calloc(1, sizeof(*c));
    if (!c) 
        return NULL;
    c->head = sub;
    c->next = NULL;
    return c;
}

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
    char   **args;
    t_cmd   *cmd_list;
    t_subcmd *sub;
    int      status;

    mini.head = NULL;
    mini.env = envp;
    mini.last_status = 0;
    while (1)
    {
        input = readline("minishell$ ");
        if (!input) 
        {                 /* Ctrl+D */
            printf("exit\n");
            break;
        }
        if (*input) 
            add_history(input);
        args = ft_split_quotes(input, ' ');
        if (args && args[0]) 
        {
            sub = new_subcmd(args);
            if (!sub) 
            { 
                perror("subcmd alloc"); 
                free_args(args); 
                free(input); 
                continue; 
            }
            cmd_list = new_cmd_with_subcmd(sub);
            if (!cmd_list) 
            { 
                perror("cmd alloc"); 
                free(sub); 
                free_args(args); 
                free(input); 
                continue; 
            }
            mini.head = cmd_list;
            status = ft_execution(cmd_list, &mini);
            mini.last_status = status;
            free_cmd_list(cmd_list);
        }
        if (args) free_args(args);
        free(input);
    }
    return 0;
}