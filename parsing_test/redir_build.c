/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:48:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 16:42:25 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/parsing.h"

// static t_redir *redir_new(t_redir_type redir_type, char *arg)
// {
//     t_redir *redir;

//     redir = (t_redir *)calloc(1, sizeof(*redir));
//     if (!redir)
//         return (NULL);
//     redir->type = redir_type;
//     if (redir_type == REDIR_HEREDOC)
//         redir->delimiter = ft_strdup(arg);
//     else
//         redir->file = ft_strdup(arg);
//     return (redir);
// }

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
	while (sub->args[i])
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
		printf("Reseting Node whihc has no next\n");
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

void	heredoc_node(t_subcmd *sub, char *arg)
{
	if (sub->cmd)
	{
		sub->next = clone(sub);
		reset(sub);
		sub->delimiter = ft_strdup(sub->next->delimiter);
		sub->type = REDIR_HEREDOC;
		sub = sub->next;
		sub->type = REDIR_INVALID;
	}
	else
	{
		sub->type = REDIR_HEREDOC;
		sub->delimiter = ft_strdup(arg);
		sub = sub->next;
	}
}

void	in_node(t_subcmd *sub, char *arg)
{
	if (sub->infile)
	{
		sub->next = clone(sub);
		reset(sub);
		sub->type = REDIR_IN;
		sub->infile = ft_strdup(sub->next->infile);
		sub = sub->next;
		free(sub->infile);
		sub->infile = ft_strdup(arg);
	}
	else
	{
		if (sub->type == REDIR_OUT)
			sub->type = REDIR_INOUT;
		else if (sub->type != REDIR_INOUT)
			sub->type = REDIR_IN;
		sub->infile = ft_strdup(arg);
	}
}

void	out_node(t_subcmd *sub, char *arg, int is_appended)
{
	if (sub->outfile)
	{
		sub->next = clone(sub);
		reset(sub);
		sub->outfile = ft_strdup(sub->next->outfile);
		sub->type = sub->next->type;
		sub = sub->next;
		sub->outfile = ft_strdup(arg);
	}
	else
	{
		if(is_appended)
			sub->type = REDIR_APPEND;
		else if (sub->type == REDIR_IN)
			sub->type = REDIR_INOUT;
		else if(sub->type != REDIR_IN && sub->type != REDIR_APPEND)
			sub->type = REDIR_OUT;
		sub->outfile = ft_strdup(arg);
	}
}

int	redir_append(t_subcmd *sub, t_redir_type redir_type, char *arg)
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