/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 10:36:28 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	safe_dup2_and_close(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (0);
	if (dup2(oldfd, newfd) == -1)
	{
		perror("minishell: dup2 error");
		close(oldfd);
		return (1);
	}
	close(oldfd);
	return (0);
}

int	open_redir_file(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	else if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

