/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:11:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 22:22:56 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int safe_dup2_and_close(int oldfd, int newfd)
{
    if (oldfd < 0)
        return (0);
    if (oldfd != newfd)
    {
        if (dup2(oldfd, newfd) == -1)
        {
            perror("minishell: dup2 error");
            close(oldfd);
            return (1);
        }
    }
    close(oldfd);
    return (0);
}

void reset_fds(int stdin_fd, int stdout_fd)
{
    if (dup2(stdin_fd, STDIN_FILENO) == -1)
        perror("MiNyanshell: dup2 restore stdin");
    close(stdin_fd);

    if (dup2(stdout_fd, STDOUT_FILENO) == -1)
        perror("MiNyanshell: dup2 restore stdout");
    close(stdout_fd);
}

void close_heredoc(t_subcmd *subcmd)
{
    if (subcmd->in_fd != -1) // heredoc já foi processado e tem fd aberto
    {
        close(subcmd->in_fd);
        subcmd->in_fd = -1;
    }
}
