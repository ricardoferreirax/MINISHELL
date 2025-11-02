/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/02 12:23:48 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_cmd *cmd_new(void);
int    arr_size(void **arr);

char **init_mini(t_mini *nyan, char *cmdline)
{
    char  **pipes;
    int     i;
    int     n;
    t_cmd  *prev;
    t_cmd  *curr;

    nyan->head = NULL;
    prev = NULL;
    pipes = split_ignore_quotes(cmdline, '|');
    if (!pipes)
        return (NULL);
    n = arr_size((void **)pipes);
    i = 0;
    while (i < n)
    {
        curr = cmd_new();
        if (!curr)
            break;
        if (!nyan->head)
            nyan->head = curr;
        if (prev)
            prev->next = curr;
        prev = curr;
        i++;
    }
    return (pipes);
}

// int pre_parse_word_count(char *str)
// {
	
// }

// char **pre_parse(char *pipe)
// {
// 	int i = 0;
// 	// char **dest;
// 	// dest = malloc(sizeof(char *) * pre_parse_word_count(pipe));
// 	while(pipe[i])
// 	{
		
// 	}
// }

void fill_mini(t_mini *nyan, char **pipes)
{
    int    i;
    t_cmd *curr;
    char **tokens;
    int    k;

    curr = nyan->head;
    i = 0;
    while (pipes && pipes[i] && curr)
    {
        tokens = split_ignore_quotes(pipes[i], ' ');
        if (tokens)
        {
            k = 0;
            while (tokens[k])
            {
                if (!parse_cmd(curr, tokens, &k))
                    break;
            }
            free_2d((void **)tokens);
        }
        curr = curr->next;
        i++;
    }
}
