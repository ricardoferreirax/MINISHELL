/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:35:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int	open_redir_fd(t_redir *redir, int *last_fd)
{
	int	new_fd;

	if (!redir || !last_fd)
		return (-1);
	if (redir->type == REDIR_IN)
		new_fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		new_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		new_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (new_fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = new_fd;
	return (0);
}

static int	process_redirs(t_cmd *cmd, int *last_in_fd, int *last_out_fd)
{
	t_redir	*redir;

	if (!cmd || !last_in_fd || !last_out_fd)
		return (1);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (open_redir_fd(redir, last_in_fd) == -1)
				return (1);
		}
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (open_redir_fd(redir, last_out_fd) == -1)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	apply_final_redirs(t_cmd *cmd, int *last_in_fd, int *last_out_fd)
{
	if (*last_in_fd != -1)
	{
		if (safe_dup2_and_close(*last_in_fd, STDIN_FILENO) != 0)
		{
			perror("MiNyanShell: failed to redirect input");
			return (1);
		}
		*last_in_fd = -1;
		cmd->in_fd = -1;
	}
	if (*last_out_fd != -1)
	{
		if (safe_dup2_and_close(*last_out_fd, STDOUT_FILENO) != 0)
		{
			perror("MiNyanShell: failed to redirect output");
			return (1);
		}
		*last_out_fd = -1;
	}
	return (0);
}

int	apply_redirs_in_child(t_cmd *cmd)
{
	int	last_in_fd;
	int	last_out_fd;

	if (!cmd)
		return (1);
	if (cmd->in_fd != -1)
		last_in_fd = cmd->in_fd;
	else
		last_in_fd = -1;
	last_out_fd = -1;
	if (process_redirs(cmd, &last_in_fd, &last_out_fd) != 0)
		return (1);
	if (apply_final_redirs(cmd, &last_in_fd, &last_out_fd) != 0)
		return (1);
	return (0);
}

int	execute_redirs_without_cmd(t_cmd *cmd, t_mini *mini)
{
	int	orig_stdin;
	int	orig_stdout;
	int	result;

	if (!cmd)
		return (0);
	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (orig_stdin == -1 || orig_stdout == -1)
		return (perror("MiNyanShell: dup original fds"), 1);
	result = apply_redirs_in_child(cmd);
	reset_fds(orig_stdin, orig_stdout);
	close_heredoc(cmd);
	mini->last_status = result;
	return (result);
}

/* int	apply_redirs_in_child(t_cmd *cmd)
{
	int	last_in_fd;
	int	last_out_fd;

	if (!cmd)
		return (1);
	if (cmd->in_fd != -1)
		last_in_fd = cmd->in_fd;
	else
		last_in_fd = -1;
	last_out_fd = -1;
	if (process_redirs(cmd, &last_in_fd, &last_out_fd) != 0)
		return (1);
	if (last_in_fd != -1)
	{
		if (safe_dup2_and_close(last_in_fd, STDIN_FILENO) != 0)
			return (perror("MiNyanShell: failed to redirect input"), 1);
		last_in_fd = -1;
		cmd->in_fd = -1;
	}
	if (last_out_fd != -1)
	{
		if (safe_dup2_and_close(last_out_fd, STDOUT_FILENO) != 0)
			return (perror("MiNyanShell: failed to redirect output"), 1);
		last_out_fd = -1;
	}
	return (0);
} */
