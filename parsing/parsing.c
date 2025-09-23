/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/23 15:00:00 by pfreire-         ###   ########.fr       */
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
	//cmd->pipe = false;
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

void	handle_redirs(t_subcmd *sub, char **tokens, int *i)
{
	if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		sub->delimiter = tokens[*i + 1];
		sub->type = REDIR_HEREDOC;
		sub = sub->next;
		(*i)++;
	}
	if ((ft_strcmp(tokens[*i], "<") == 0))
		redir_in(sub, tokens, i);
	if ((ft_strcmp(tokens[*i], ">")) == 0 || ft_strcmp(tokens[*i], ">>") == 0)
		redir_out(sub, tokens, i);
}

int	arg_nbr(char **tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i + j] != NULL && !is_redir(tokens[i + j]))
		j++;
	return (j);
}

void	handle_command(t_subcmd *sub, char **tokens, int *i)
{
	int	j;

	j = 0;
	sub->cmd = ft_strdup(tokens[*i]);
	sub->args = malloc(sizeof(char *) * arg_nbr(tokens, *i));
	if (!sub->args)
		exit(1);
	while (tokens[*i] != NULL && !is_redir(tokens[*i]))
	{
		sub->args[j] = tokens[*i];
		(*i)++;
		j++;
	}
	while (tokens[*i] != NULL)
	{
		handle_redirs(sub, tokens, i);
	}
}

void	fill_subcmd(t_cmd *node, char **tokens)
{
	int			j;
	t_subcmd	*sub;

	j = 0;
	(void) node;
	while (tokens[j] != NULL)
	{
		sub = subcmd_new();
		if (is_redir(tokens[j]))
			handle_redirs(sub, tokens, &j);
		else
			handle_command(sub, tokens, &j);
		j++;
	}
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
		fill_subcmd(curr, tokens);
		curr = curr->next;
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
