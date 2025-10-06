/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:50:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/05 20:51:53 by rmedeiro         ###   ########.fr       */
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

void free_redir_list(t_redir *r)
{
    t_redir *cur;
    t_redir *nxt;

    cur = r;
    while (cur)
    {
        nxt = cur->next;
        if (cur->file)
            free(cur->file);
        if (cur->delimiter)
            free(cur->delimiter);
        free(cur);
        cur = nxt;
    }
}

void free_cmd_list(t_cmd *head)
{
    t_cmd *cur;
    t_cmd *nxt;
    int i;

    cur = head;
    while (cur)
    {
        if (cur->in_fd != -1)
        {
            close(cur->in_fd);
            cur->in_fd = -1;
        }
        if (cur->cmd_args)
        {
            i = 0;
            while (cur->cmd_args[i])
            {
                free(cur->cmd_args[i]);
                i++;
            }
            free(cur->cmd_args);
            cur->cmd_args = NULL;
        }
        if (cur->redirs)
        {
            free_redir_list(cur->redirs);
            cur->redirs = NULL;
        }
        nxt = cur->next;
        free(cur);
        cur = nxt;
    }
}