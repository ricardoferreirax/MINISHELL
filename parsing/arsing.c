/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arsing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/22 17:24:58 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"
#include <stdbool.h>
#include <string.h>

// char	*isolate_command(char *cmd)
// {
// 	char	**arr;

// 	arr = split_ignore_quotes(cmd, ' ');
// 	return (arr[0]);
// }

// t_subcmd	*sublist_creator(char *cmd)
// {
// 	t_subcmd	*filler;
// 	char		**arr;

// 	filler = malloc(sizeof(t_subcmd));
// 	arr = split_ignore_quotes(cmd, ' ');
// 	filler->cmd = arr[0];
// 	filler->args = arr;
// 	filler->next = NULL;
// 	return (filler);
// }

// t_cmd	*list_creator(char *cmd)
// {
// 	t_cmd	*head;
// 	t_cmd	*filler;
// 	char	**arr;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	head = malloc(sizeof(t_cmd));
// 	arr = split_ignore_quotes(cmd, '|');
// 	filler = head;
// 	while (arr[i] != NULL)
// 	{
// 		head->head = sublist_creator(cmd);
// 		while (filler->head->args[j])
// 			j++;
// 		// printf("%s\n", filler->head->args[j++]);
// 		i++;
// 		filler->head->next = NULL;
// 		filler->head = filler->head->next;
// 	}
// 	return (head);
// }

// int	arr_size(void **arr)
// {
// 	int	i;

// 	i = 0;
// 	if (!arr)
// 		return (0);
// 	while (arr[i] != NULL)
// 		i++;
// 	return (i);
// }

// t_cmd	*cmd_new(void)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	cmd->head = subcmd_new();
// 	cmd->next = NULL;
// 	cmd->pipe = false;
// 	return (cmd);
// }

// char	**init_mini(t_mini *nyan, char *cmd)
// {
// 	int		i;
// 	t_cmd	*curr;
// 	t_cmd	*prev;
// 	char	**pipes;
// 	int		cmd_nbr;

// 	prev = NULL;
// 	i = 0;
// 	pipes = split_ignore_quotes(cmd, '|');
// 	cmd_nbr = arr_size((void **)pipes);
// 	while (i < cmd_nbr)
// 	{
// 		curr = cmd_new();
// 		if (!nyan->head)
// 			nyan->head = curr;
// 		if (prev)
// 			prev->next = curr;
// 		prev = curr;
// 		i++;
// 	}
// 	return (pipes);
// }

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

bool	is_redir(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, ">>", 2) == 0
		|| ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (true);
	return (false);
}

void redir_in(t_subcmd *sub, char **tokens, int *i)
{
	if(sub->infile)
		sub = sub->next;
	sub->infile = tokens[*i + 1];
	i++;
}

void redir_out(t_subcmd *sub, char **tokens, int *i)
{
	if(sub->outfile)
	{
		sub = sub->next;
	}
	sub->outfile = tokens[*i + 1];
	if(ft_strcmp(tokens[*i], ">>") == 0)
		sub->type = REDIR_APPEND;
	i++;
}

void	handle_redirs(t_subcmd *sub, char **tokens, int *i)
{
	if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		sub->delimiter = tokens[*i + 1];
		sub->type = REDIR_HEREDOC;
		sub = sub->next;
		i++;
	}
	if((ft_strcmp(tokens[*i], "<") == 0))
		redir_in(sub, tokens, i);
	if((ft_strcmp(tokens[*i], ">")) || ft_strcmp(tokens[*i ], ">>"))
		redir_out(sub, tokens, i);
	
}

void handle_command(t_subcmd *sub, char **tokens, int *i)
{
	
}

void	fill_subcmd(t_cmd *node, char **tokens)
{
	int			*j;
	t_subcmd	*sub;

	(*j) = 0;
	while (tokens[*j] != NULL)
	{
		sub = sub_cmdnew();
		if (is_redir(tokens[*j]))
			handle_redirs(sub, tokens, j);
		else
			handle_command(sub, tokens, j);
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
