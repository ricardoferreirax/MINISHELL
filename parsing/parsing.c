/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/27 16:49:05 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"
#include <stdbool.h>
#include <string.h>

t_subcmd	*subcmd_new(void);

int	arr_size(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i] != NULL)
		i++;
	return (i);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->head = subcmd_new();
	cmd->next = NULL;
	// cmd->pipe = false;
	return (cmd);
}

char	**init_mini(t_mini *nyan, char *cmd)
{
	int		i;
	t_cmd	*curr;
	t_cmd	*prev;
	char	**pipes;
	int		cmd_nbr;

	prev = NULL;
	i = 0;
	pipes = split_ignore_quotes(cmd, '|');
	cmd_nbr = arr_size((void **)pipes);
	while (i < cmd_nbr)
	{
		curr = cmd_new();
		if (!nyan->head)
			nyan->head = curr;
		if (prev)
			prev->next = curr;
		prev = curr;
		i++;
	}
	return (pipes);
}

t_subcmd	*subcmd_new(void)
{
	t_subcmd	*sub;

	sub = malloc(sizeof(t_subcmd));
	if (!sub)
		return (NULL);
	sub->type = REDIR_INVALID;
	sub->delimiter = NULL;
	sub->args = NULL;
	sub->cmd = NULL;
	sub->infile = NULL;
	sub->outfile = NULL;
	sub->next = NULL;
	sub->redirs = NULL;
	sub->cmd_type = NONE_CMD;
	sub->in_fd = -1;
	sub->out_fd = -1;
	return (sub);
}

t_subcmd	*sub_cmdappend(t_subcmd *curr)
{
	curr->next = subcmd_new();
	return (curr->next);
}

bool	is_redir(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str,
			"<") == 0 || ft_strcmp(str, "<<") == 0)
		return (true);
	return (false);
}

void	redir_in(t_subcmd *sub, char **tokens, int *i)
{
	if (sub->infile)
		sub = sub_cmdappend(sub);
	sub->infile = tokens[*i + 1];
	(*i)++;
}

void	redir_out(t_subcmd *sub, char **tokens, int *i)
{
	if (sub->outfile)
	{
		sub = sub_cmdappend(sub);
	}
	sub->outfile = tokens[*i + 1];
	if (ft_strcmp(tokens[*i], ">>") == 0)
		sub->type = REDIR_APPEND;
	(*i)++;
}

int	arg_nbr(char **tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i + j] != NULL && !is_redir(tokens[i + j]))
		j++;
	return (j);
}


void	add_arg(t_subcmd *sub, char *token)
{
	int		count;
	char	**new_arg;
	int		i;

	count = 0;
	if (!sub->args)
	{
		sub->args = malloc(sizeof(char *) * 2);
		sub->args[0] = ft_strdup(token);
		sub->args[1] = NULL;
		return ;
	}
	while (sub->args[count])
		count++;
	new_arg = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_arg[i] = sub->args[i];
		i++;
	}
	new_arg[count] = ft_strdup(token);
	new_arg[count + 1] = NULL;
	free(sub->args);
	sub->args = new_arg;
}

t_subcmd	*clone_out(t_subcmd *sub, char *outfile)
{
	t_subcmd	*clone;

	clone = malloc(sizeof(t_subcmd));
	if (!clone)
		return (NULL);
	clone->type = sub->type;
	clone->delimiter = ft_strdup(sub->delimiter);
	clone->args = malloc(sizeof(char *) * (arr_size((void **)sub->args) + 1));
	int i = 0;
	while(sub->args && sub->args[i])
	{
		clone->args[i] = ft_strdup(sub->args[i]);
		i++;
	}
	clone->args[i] = NULL;
	clone->cmd = ft_strdup(sub->cmd);
	clone->outfile = ft_strdup(outfile);
	clone->infile = ft_strdup(sub->infile);
	clone->redirs = sub->redirs;
	clone->cmd_type = sub->cmd_type;
	clone->in_fd = sub->in_fd;
	clone->out_fd = sub->out_fd;
	return (clone);
}

t_subcmd	*clone_in(t_subcmd *sub, char *infile)
{
	t_subcmd	*clone;

	clone = malloc(sizeof(t_subcmd));
	if (!clone)
		return (NULL);
	clone->type = sub->type;
	clone->delimiter = ft_strdup(sub->delimiter);
	int i = 0;
	clone->args = malloc(sizeof(char *) * (arr_size((void **)sub->args) + 1));
	while(sub->args && sub->args[i])
	{
		clone->args[i] = ft_strdup(sub->args[i]);
		i++;
	}
	clone->args[i] = NULL;
	clone->cmd = ft_strdup(sub->cmd);
	clone->infile = ft_strdup(infile);
	clone->outfile = ft_strdup(sub->outfile);
	clone->next = sub->next;
	clone->redirs = sub->redirs;
	clone->cmd_type = sub->cmd_type;
	clone->in_fd = sub->in_fd;
	clone->out_fd = sub->out_fd;
	return (clone);
}

void	reset_in(t_subcmd *sub)
{
	sub->type = REDIR_IN;
	if(sub->delimiter)
		free(sub->delimiter);
	sub->delimiter = NULL;
	if(sub->args)
		free_2d((void**) sub->args);
	sub->args = NULL;
	if(sub->cmd)
		free(sub->cmd);
	sub->cmd = NULL;
	if(sub->outfile)
		free(sub->outfile);
	sub->outfile = NULL;

	sub->in_fd = -1;
	sub->out_fd = -1;
}

void	reset_out(t_subcmd *sub)
{
	sub->type = REDIR_OUT;
	if(sub->delimiter)
		free(sub->delimiter);
	sub->delimiter = NULL;
	if(sub->args)
		free_2d((void **)sub->args);
	sub->args = NULL;
	if(sub->cmd)
		free(sub->cmd);
	sub->cmd = NULL;
	if(sub->infile)
		free(sub->infile);
	sub->infile = NULL;
	sub->in_fd = -1;
	sub->out_fd = -1;
}

bool	parse(t_subcmd *sub, char **tokens, int *i)
{
	bool	new_node;

	new_node = false;
	if (tokens[*i] && !is_redir(tokens[*i]))
	{
		if (!sub->cmd)
		{
			sub->cmd = ft_strdup(tokens[*i]);
		}
		while (tokens[*i] && !is_redir(tokens[*i]))
		{
			add_arg(sub, tokens[*i]);
			(*i)++;
		}
	}
	else if (tokens[*i] && ft_strcmp(tokens[*i], "<<") == 0)
	{
		if (sub->delimiter)
		{
			new_node = true;
			sub = sub->next;
		}
		sub->type = REDIR_HEREDOC;
		(*i)++;
		sub->delimiter = ft_strdup(tokens[*i]);
		(*i)++;
		new_node = true;
		sub = sub->next;
	}
	else if (tokens[*i] && ((ft_strcmp(tokens[*i], ">>") == 0)
			|| (ft_strcmp(tokens[*i], ">") == 0)))
	{
		sub->type = REDIR_OUT;
		if (ft_strcmp(tokens[*i], ">>") == 0)
			sub->type = REDIR_APPEND;
		(*i)++;
		if (sub->outfile)
		{
			sub->next = clone_out(sub, tokens[*i]);
			reset_out(sub);
			sub = sub->next;
		}
		else
			sub->outfile = ft_strdup(tokens[*i]);
		(*i)++;
	}
	else if (tokens[*i] && ft_strcmp(tokens[*i], "<") == 0)
	{
		sub->type = REDIR_IN;
		(*i)++;
		if(sub->infile)
		{
			sub->next = clone_in(sub, tokens[*i]);
			reset_in(sub);
			sub = sub->next;
			
		}
		else
			sub->infile = ft_strdup(tokens[*i]);
		(*i)++;
	}
	return (new_node);
}

void	fill_subcmd(t_cmd *node, char **tokens)
{
	int			j;
	t_subcmd	*curr;
	t_subcmd	*prev;
	t_subcmd	*head;
	bool		new_node;

	new_node = false;
	head = NULL;
	curr = NULL;
	prev = NULL;
	j = 0;
	curr = subcmd_new();
	while (tokens[j] != NULL)
	{
		if (!head)
			head = curr;
		if (prev)
			prev->next = curr;
		new_node = parse(curr, tokens, &j);
		if (new_node)
		{
			prev = curr;
			curr = subcmd_new();
		}
	}
	node->head = head;
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s ", tokens[i]);
		i++;
	}
	printf("\n");
}

void	fill_mini(t_mini *nyan, char **pipes)
{
	int		i;
	t_cmd	*curr;
	char	**tokens;

	i = 0;
	curr = nyan->head;
	while (pipes[i])
	{
		tokens = split_ignore_quotes(pipes[i], ' ');
		print_tokens(tokens);
		fill_subcmd(curr, tokens);
		free_2d((void **)tokens);
		i++;
	}
}

t_mini	parser(char *cmd, char **env)
{
	t_mini	nyan;
	char	**pipes;

	nyan.env = env;
	nyan.head = NULL;
	pipes = init_mini(&nyan, cmd);
	fill_mini(&nyan, pipes);
	return (nyan);
}
