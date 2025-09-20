/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/20 15:53:28 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

static void handle_redir_in(t_redir *redir)
{
    int fd = open(redir->file, O_RDONLY);
    if (fd < 0)
        error_exit("minishell: infile open failed");
    safe_dup2_and_close(fd, STDIN_FILENO);
}

static void handle_redir_out(t_redir *redir)
{
    int fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        error_exit("minishell: outfile open failed");
    safe_dup2_and_close(fd, STDOUT_FILENO);
}

static void handle_redir_append(t_redir *redir)
{
    int fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        error_exit("minishell: outfile append open failed");
    safe_dup2_and_close(fd, STDOUT_FILENO);
}

static void handle_redir_heredoc(t_subcmd *subcmd)
{
    safe_dup2_and_close(subcmd->in_fd, STDIN_FILENO);
}

void handle_redirs(t_subcmd *subcmd)
{
    t_redir *redir = subcmd->redirs;

    while (redir)
    {
        if (redir->type == REDIR_IN)
            handle_redir_in(redir);
        else if (redir->type == REDIR_OUT)
            handle_redir_out(redir);
        else if (redir->type == REDIR_APPEND)
            handle_redir_append(redir);
        else if (redir->type == REDIR_HEREDOC)
            handle_redir_heredoc(subcmd);
        else if (redir->type == REDIR_INVALID)
            error_exit("minishell: invalid redirection type");
        redir = redir->next;
    }
}
