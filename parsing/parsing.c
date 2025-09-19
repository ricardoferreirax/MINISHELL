/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/19 11:48:11 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"

char	*isolate_command(char *cmd)
{
	char	**arr;

	arr = split_ignore_quotes(cmd, ' ');
	return (arr[0]);
}

t_subcmd	*sublist_creator(char *cmd)
{
	t_subcmd	*filler;
	char		**arr;

	filler = malloc(sizeof(t_subcmd));
	arr = split_ignore_quotes(cmd, ' ');
	filler->cmd = arr[0];
	filler->args = arr;
	filler->next = NULL;
	return (filler);
}

t_cmd	*list_creator(char *cmd)
{
	t_cmd	*head;
	t_cmd	*filler;
	char	**arr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	head = malloc(sizeof(t_cmd));
	arr = split_ignore_quotes(cmd, '|');
	filler = head;
	while (arr[i] != NULL)
	{
		head->head = sublist_creator(cmd);
		while (filler->head->args[j])
			j++;
		// printf("%s\n", filler->head->args[j++]);
		i++;
		filler->head->next = NULL;
		filler->head = filler->head->next;
	}
	return (head);
}

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

t_subcmd	*subcmd_new(void)
{
	t_subcmd	*sc;

	sc = malloc(sizeof(t_subcmd));
	sc->delimiter = NULL;
	sc->args = NULL;
	sc->cmd = NULL;
	sc->infile = NULL;
	sc->outfile = NULL;
	sc->next = NULL;
	sc->last = NULL;
	sc->in_fd = -1;
	sc->out_fd = -1;
	return (sc);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->head = subcmd_new();
	cmd->next = NULL;
	cmd->pipe = false;
	return (cmd);
}

t_mini	parser(char *cmd, char **env)
{
	t_mini	nyan;
	char	**pipes;
	int		i;
	int		cmd_nbr;
	t_cmd	*curr;
	t_cmd	*prev;

	nyan.env = env;
	nyan.head = NULL;
	prev = NULL;
	pipes = split_ignore_quotes(cmd, '|');
	i = 0;
	cmd_nbr = arr_size((void **)pipes);
	while (i < cmd_nbr)
	{
		curr = cmd_new();
		if (!nyan.head)
			nyan.head = curr;
		if (prev)
			prev->next = curr;
		prev = curr;
		i++;
	}
	return (nyan);
}
