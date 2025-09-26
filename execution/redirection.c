/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 23:12:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

static int	handle_single_redir(t_redir *redir, int *last_fd)
{
	int	new_fd;

	if (*last_fd != -1) // Fecha o fd anterior, se já existia
		close(*last_fd);
	if (redir->type == REDIR_IN)
		new_fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		new_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		new_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else // Tipo inválido
		return (-1);
	if (new_fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	*last_fd = new_fd; // Atualiza o último fd aberto
	return (0);
}

static int handle_redir(t_redir *redir, int *last_fd)
{
	if (handle_single_redir(redir, last_fd) == -1)
	{
		if (*last_fd != -1)
		{
			close(*last_fd);
			*last_fd = -1;
		}
		return (1);
	}
	return (0);
}

static int process_redirs(t_subcmd *sub, int *last_in_fd, int *last_out_fd)
{
	t_redir	*redir;

	redir = sub->redirs;
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
		{
			if ((redir->type == REDIR_IN && handle_redir(redir, last_in_fd))
				|| ((redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
					&& handle_redir(redir, last_out_fd)))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

int handle_redirs_in_child(t_subcmd *sub)
{
    int last_in_fd;
    int last_out_fd;

    if (sub->in_fd != -1) // se o heredoc já foi processado
        last_in_fd = sub->in_fd; 
    else
        last_in_fd = -1;
    last_out_fd = -1;
    if (process_redirs(sub, &last_in_fd, &last_out_fd))
        return (1);
    if (last_in_fd != -1)
    {
        if (safe_dup2_and_close(last_in_fd, STDIN_FILENO) != 0)
            return (perror("MiNyanshell: failed to redirect input"), 1);
        last_in_fd = -1;
    }
    if (last_out_fd != -1)
    {
        if (safe_dup2_and_close(last_out_fd, STDOUT_FILENO) != 0)
            return (perror("MiNyanshell: failed to redirect output"), 1);
        last_out_fd = -1;
    }
    return (0); // Sucesso
}

int	handle_single_redir_only(t_cmd *cmd, t_mini *mini)
{
	t_subcmd	*sub;
	int			orig_stdin;
	int			orig_stdout;
	int			result;

	if (!cmd || !cmd->head)
		return (0);
	sub = cmd->head;
	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (orig_stdin == -1 || orig_stdout == -1)
		return (perror("MiNyanshell: dup original fds"), 1);
	result = handle_redirs_in_child(sub);
	reset_fds(orig_stdin, orig_stdout);
	if (sub->in_fd != -1)
	{
		close(sub->in_fd);
		sub->in_fd = -1;
	}
	mini->last_status = result;
	return (result);
}
