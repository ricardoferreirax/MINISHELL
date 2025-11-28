/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:50:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/28 14:39:54 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/execution.h"



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
        free_2d((void **)current->args);
        free_redirs(current->redirs);
        free(current);
        current = next;
    }
    *head_ptr = NULL;
}
