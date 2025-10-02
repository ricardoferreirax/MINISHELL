/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:48:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/02 12:01:20 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "../execution/execution.h"
#include "parsing.h"

t_subcmd	*clone(t_subcmd *sub)
{
	t_subcmd	*clone;
	int			i;

	clone = malloc(sizeof(t_subcmd));
	if (!clone)
		return (NULL);
	clone->type = sub->type;
	clone->delimiter = ft_strdup(sub->delimiter);
	clone->args = malloc(sizeof(char *) * (arr_size((void **)sub->args) + 1));
	i = 0;
	while (sub->args && sub->args[i])
	{
		clone->args[i] = ft_strdup(sub->args[i]);
		i++;
	}
	clone->args[i] = NULL;
	clone->cmd = ft_strdup(sub->cmd);
	clone->outfile = ft_strdup(sub->outfile);
	clone->infile = ft_strdup(sub->infile);
	clone->type = sub->type;
	clone->in_fd = sub->in_fd;
	clone->out_fd = sub->out_fd;
	return (clone);
}

void	reset(t_subcmd *sub)
{
	if (!sub->next)
		printf("Reseting Node of which has no next node (Are you sure this is what it should be doing?)\n");
	if (sub->delimiter)
		free(sub->delimiter);
	sub->delimiter = NULL;
	if (sub->args)
		free_2d((void **)sub->args);
	sub->args = NULL;
	if (sub->cmd)
		free(sub->cmd);
	sub->cmd = NULL;
	if (sub->infile)
		free(sub->infile);
	sub->infile = NULL;
	if (sub->outfile)
		free(sub->outfile);
	sub->outfile = NULL;
	sub->in_fd = -1;
	sub->out_fd = -1;
}

void	heredoc_node(t_subcmd **sub, char *arg)
{
	t_subcmd	*curr;

	curr = *sub;
	if (curr->cmd)
	{
		curr->next = clone(curr);
		reset(curr);
		curr->delimiter = ft_strdup(arg);
		curr->type = REDIR_HEREDOC;
		curr = curr->next;
	}
	else
	{
		curr->type = REDIR_HEREDOC;
		curr->delimiter = ft_strdup(arg);
		curr = curr->next;
	}
	*sub = curr;
}

void	in_node(t_subcmd **sub, char *arg)
{
	t_subcmd	*curr;

	curr = *sub;
	if (curr->infile)
	{
		curr->next = clone(curr);
		reset(curr);
		curr->type = REDIR_IN;
		curr->infile = ft_strdup(curr->next->infile);
		curr = curr->next;
		free(curr->infile);
		curr->infile = ft_strdup(arg);
	}
	else
	{
		if (curr->type == REDIR_OUT)
			curr->type = REDIR_INOUT;
		else if (curr->type != REDIR_INOUT && curr->type != REDIR_APPEND)
			curr->type = REDIR_IN;
		curr->infile = ft_strdup(arg);
	}
	*sub = curr;
}

void	out_node(t_subcmd **sub, char *arg, int is_appended)
{
	t_subcmd	*curr;

	curr = *sub;
	if (curr->outfile)
	{
		curr->next = clone(curr);
		reset(curr);
		curr->outfile = ft_strdup(curr->next->outfile);
		curr->type = curr->next->type;
		if (is_appended)
			curr->next->type = REDIR_APPEND;
		else if (curr->next->type != REDIR_INOUT)
			curr->next->type = REDIR_OUT;
		curr = curr->next;
		free(curr->outfile);
		curr->outfile = ft_strdup(arg);
	}
	else
	{
		if (is_appended)
			curr->type = REDIR_APPEND;
		else if (curr->type == REDIR_IN)
			curr->type = REDIR_INOUT;
		else if (curr->type != REDIR_IN && curr->type != REDIR_APPEND)
			curr->type = REDIR_OUT;
		curr->outfile = ft_strdup(arg);
	}
	*sub = curr;
}

bool	is_redir(char *str)
{
	if (!str)
	return (false);
if (ft_strcmp(str, "<") == 0)
return (true);
if (ft_strcmp(str, ">") == 0)
return (true);
if (ft_strcmp(str, ">>") == 0)
return (true);
if (ft_strcmp(str, "<<") == 0)
return (true);
return (false);
}

int	redir_append(t_subcmd **sub, t_redir_type redir_type, char *arg)
{
	if (redir_type == REDIR_HEREDOC)
		heredoc_node(sub, arg);
	if (redir_type == REDIR_IN)
		in_node(sub, arg);
	if (redir_type == REDIR_APPEND)
		out_node(sub, arg, 1);
	if (redir_type == REDIR_OUT)
		out_node(sub, arg, 0);
	return (0);
}
