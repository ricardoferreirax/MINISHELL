/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:37:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 17:03:37 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

static int	open_redir_fd(t_subcmd *sub, int *last_fd)
{
	int	new_fd;

	if (sub->type == REDIR_IN)
		new_fd = open(sub->infile, O_RDONLY);
	else if (sub->type == REDIR_OUT)
		new_fd = open(sub->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (sub->type == REDIR_APPEND)
		new_fd = open(sub->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (new_fd == -1)
	{
		if(sub->type == REDIR_IN)
			perror(sub->infile);
		else
			perror(sub->outfile);
		return (-1);
	}
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = new_fd; // atualiza o último fd aberto
	return (0);
}

static int	process_redirs(t_subcmd *subcmd, int *last_in_fd, int *last_out_fd)
{
	if (!subcmd)
		return (0);
	while (subcmd)
	{
		if (subcmd->type == REDIR_IN)
		{
			if (open_redir_fd(subcmd, last_in_fd) == -1)
				return (1);
		}
		else if (subcmd->type == REDIR_OUT || subcmd->type == REDIR_APPEND)
		{
			if (open_redir_fd(subcmd, last_out_fd) == -1)
				return (1);
		}
		subcmd = subcmd->next;
	}
	return (0);
}

int	apply_redirs_in_child(t_subcmd *sub)
{
	int	last_in_fd;
	int	last_out_fd;

	if (sub->in_fd != -1)        // se o heredoc já foi processado
		last_in_fd = sub->in_fd; // o last_in_fd começa com o fd do heredoc
	else
		last_in_fd = -1;
	// senão começa sem as redireções de input
	last_out_fd = -1;
	// começa sem redireções de output
	if (process_redirs(sub, &last_in_fd, &last_out_fd))
		// processa todas as redireções (menos os heredocs)
		return (1);
	if (last_in_fd != -1) // se houve uma redireção de input, aplica-a
	{
		if (safe_dup2_and_close(last_in_fd, STDIN_FILENO) != 0)
			return (perror("MiNyanshell: failed to redirect input"), 1);
		last_in_fd = -1; // já foi aplicada então marcamos como fechada
	}
	if (last_out_fd != -1) // se houve uma redireção de output, aplica-a
	{
		if (safe_dup2_and_close(last_out_fd, STDOUT_FILENO) != 0)
			return (perror("MiNyanshell: failed to redirect output"), 1);
		last_out_fd = -1;
	}
	return (0); // Sucesso
}

int	run_redirs_without_cmd(t_cmd *cmd, t_mini *mini)
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
	result = apply_redirs_in_child(sub);
	reset_fds(orig_stdin, orig_stdout);
	if (sub->in_fd != -1)
	{
		close(sub->in_fd);
		sub->in_fd = -1;
	}
	mini->last_status = result;
	return (result);
}
