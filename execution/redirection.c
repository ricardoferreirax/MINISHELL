/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 11:28:06 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

void handle_redirs(t_subcmd *subcmd)
{
	t_redir *redir;
	int fd;

	redir = subcmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
				error_exit("minishell: infile open failed");
			safe_dup2_and_close(fd, STDIN_FILENO);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				error_exit("minishell: outfile open failed");
			safe_dup2_and_close(fd, STDOUT_FILENO);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				error_exit("minishell: outfile append open failed");
			safe_dup2_and_close(fd, STDOUT_FILENO);
		}
		else if (redir->type == REDIR_HEREDOC)
			safe_dup2_and_close(subcmd->in_fd, STDIN_FILENO);
		else if (redir->type == REDIR_INVALID)
			error_exit("minishell: invalid redirection type");
		redir = redir->next;
	}
}


