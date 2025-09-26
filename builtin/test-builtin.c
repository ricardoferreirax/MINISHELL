/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:12:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/25 16:05:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "utils.h"

typedef struct s_subcmd {
    char **args;
}   t_subcmd;

static void free_args(char **args)
{
    int i = 0;
    if (!args) return;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

static char **split_args(char *input)
{
    char **args;
    char *token;
    int i = 0;

    args = malloc(100 * sizeof(char *));
    token = strtok(input, " ");
    while (token)
    {
        args[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}

int exec_builtin(t_subcmd *subcmd, t_mini *mini)
{
    char *cmd;

    if (!subcmd || !subcmd->args || !subcmd->args[0])
        return (0);
    cmd = subcmd->args[0];
    if (strcmp(cmd, "echo") == 0)
        return ft_echo(subcmd, mini);
    else if (strcmp(cmd, "pwd") == 0)
        return ft_pwd(subcmd, mini);
    // else if (strcmp(cmd, "env") == 0)
    //     return ft_env(subcmd, mini);
    // else if (strcmp(cmd, "exit") == 0)
    //     return ft_exit(subcmd, mini);
    // else if (strcmp(cmd, "export") == 0)
    //     return ft_export(subcmd, mini);
    // else if (strcmp(cmd, "unset") == 0)
    //     return ft_unset(subcmd, mini);
    // else if (strcmp(cmd, "cd") == 0)
    //     return ft_cd(subcmd, mini);
    return (1);
}


int main(void)
{
    char    *input;
    char    **args;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input) // CTRL+D
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);

        args = ft_split_quotes(input, ' ');
        if (args && args[0] && ft_strcmp(args[0], "echo") == 0)
            ft_echo(subcmd, &mini);
        else if (args && args[0])
            printf("Comando não suportado: %s\n", args[0]);

        free_args(args);
        free(input);
        printf("--------------------------------------------------\n");
    }
    return (0);
}
