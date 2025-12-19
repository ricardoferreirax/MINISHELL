/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:29:35 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/19 08:28:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

void	close_heredoc(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->in_fd != -1)
	{
		close_fd_safe(&cmd->in_fd);
		cmd->in_fd = -1;
	}
}

void	close_fd_safe(int *fd)
{
	if (fd && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_all_heredoc_fds(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		if (current->in_fd != -1)
		{
			close(current->in_fd);
			current->in_fd = -1;
		}
		current = current->next;
	}
}

void	close_my_pipes(t_pipe_pos pos, t_pipeline *pp)
{
	if (!pp)
		return ;
	if (pos == FIRST)
	{
		close_fd_safe(&pp->pipefd[0]);
		close_fd_safe(&pp->pipefd[1]);
	}
	else if (pos == MIDDLE)
	{
		close_fd_safe(&pp->prev_pipefd);
		close_fd_safe(&pp->pipefd[0]);
		close_fd_safe(&pp->pipefd[1]);
	}
	else if (pos == LAST)
		close_fd_safe(&pp->prev_pipefd);
}
