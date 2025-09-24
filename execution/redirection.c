/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/23 23:41:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

/* static void handle_redir_in(t_redir *redir)
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
} */

static int handle_input_redir(t_subcmd *subcmd, int saved_stdout, int saved_stdin)
{
    if (!subcmd->infile && subcmd->in_fd != -2) // sem infile e sem heredoc
        return (1);
    if (subcmd->in_fd == -2) // heredoc
    {
        subcmd->in_fd = handle_heredoc(subcmd);
        if (subcmd->in_fd == -1)
        {
            close(saved_stdout);
            close(saved_stdin);
            return (0);
        }
    }
    else
    {
        subcmd->in_fd = open(subcmd->infile, O_RDONLY);
        if (subcmd->in_fd == -1)
        {
            perror("minishell: no such file or directory");
            close(saved_stdout);
            close(saved_stdin);
            return 0;
        }
    }

    if (safe_dup2_and_close(subcmd->in_fd, STDIN_FILENO) != 0)
    {
        close(saved_stdout);
        close(saved_stdin);
        return 0;
    }
    subcmd->in_fd = -1;
    return 1;
}

static int handle_output_redir(t_subcmd *subcmd, int saved_stdout, int saved_stdin)
{
    if (!subcmd->outfile)
        return 1;
    if (subcmd->cmd_type == REDIR_APPEND)
        subcmd->out_fd = open(subcmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        subcmd->out_fd = open(subcmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (subcmd->out_fd == -1)
    {
        perror("minishell: cannot open output file");
        if (subcmd->infile)
            safe_dup2_and_close(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
        return 0;
    }
    if (safe_dup2_and_close(subcmd->out_fd, STDOUT_FILENO) != 0)
    {
        perror("minishell: failed to redirect output");
        if (subcmd->infile)
            safe_dup2_and_close(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
        return 0;
    }
    subcmd->out_fd = -1;
    return 1;
}

int handle_redirections(t_subcmd *subcmd)
{
    int saved_stdout;
    int saved_stdin;

    if (!subcmd)
        return (0);
    saved_stdout = dup(STDOUT_FILENO);
    saved_stdin  = dup(STDIN_FILENO);
    if (saved_stdout == -1 || saved_stdin == -1)
    {
        if (saved_stdout != -1)
            close(saved_stdout);
        if (saved_stdin != -1)
            close(saved_stdin);
        return (0);
    }
    if (!handle_input_redir(subcmd, saved_stdout, saved_stdin))
        return (0);
    if (!handle_output_redir(subcmd, saved_stdout, saved_stdin))
        return (0);
    close(saved_stdout);
    close(saved_stdin);
    return (1);
}
