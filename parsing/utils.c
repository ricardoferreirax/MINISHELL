/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:50:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/14 20:27:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

void	update_quote_state(char c, bool *inquote, bool *indquote)
{
	if (c == '\'' && !(*indquote))
		*inquote = !(*inquote);
	else if (c == '\"' && !(*inquote))
		*indquote = !(*indquote);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*next;

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

void	free_cmd_list(t_cmd **head_ptr)
{
	t_cmd	*current;
	t_cmd	*next;

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
