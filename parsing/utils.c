/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:50:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 10:02:46 by rmedeiro         ###   ########.fr       */
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
    int i;

    if (!argv)
        return ;
    i = 0;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

void free_redirs(t_redir *redir)
{
    t_redir *next;

    while (redir)
    {
        next = redir->next;
        if (redir->file)
            free(redir->file);
        if (redir->delimiter)
            free(redir->delimiter);
        free(redir);
        redir = next;
    }
}

void free_cmd_list(t_cmd **head_ptr)
{
    t_cmd *current;
    t_cmd *next;

    if (!head_ptr || !*head_ptr)
        return ;
    current = *head_ptr;
    while (current)
    {
        next = current->next;
        close_fd_safe(&current->in_fd);
        free_argv(current->args);
        free_redirs(current->redirs);
        free(current);
        current = next;
    }
    *head_ptr = NULL;
}
