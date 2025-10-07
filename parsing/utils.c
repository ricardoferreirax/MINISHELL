/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:50:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 19:50:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "../include/parsing.h"
#include "../include/execution.h"

char	*skip_whitespaces(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

int arr_size(void **arr)
{
    int i;

    i = 0;
    if (!arr) 
        return (0);
    while (arr[i]) 
        i++;
    return (i);
}

void free_argv(char **argv)
{
    int i = 0;
    if (!argv) return;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

void free_redirs(t_redir *r)
{
    t_redir *next;

    while (r)
    {
        next = r->next;
        if (r->file)      
            free(r->file);
        if (r->delimiter)
            free(r->delimiter);
        free(r);
        r = next;
    }
}

void free_cmd_list(t_cmd *head)
{
    t_cmd *cur;
    t_cmd *next;

    cur = head;
    while (cur)
    {
        next = cur->next;

        if (cur->in_fd != -1) 
        { 
            close(cur->in_fd); 
            cur->in_fd = -1; 
        }
        free_argv(cur->cmd_args);
        free_redirs(cur->redirs);
        free(cur);
        cur = next;
    }
}
