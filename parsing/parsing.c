/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:52:11 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/17 16:43:35 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h" w

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
	filler->next= NULL;
	return(filler);
}

t_cmd	*list_creator(char *cmd)
{
	t_cmd	*head;
	t_cmd	*filler;
	char	**arr;
	int		i;
	int		j;

	i = 0;
	head = malloc(sizeof(t_cmd));
	arr = split_ignore_quotes(cmd, '|');
	filler = head;
	while (arr[i] != NULL)
	{
		head->head=sublist_creator(cmd);
		while (filler->head->args[j])
			printf("%s\n", filler->head->args[j++]);
		i++;
		filler->head->next = NULL;
		filler->head = filler->head->next;
	}
	return (head);
}

t_mini	parser(char *cmd, char **env)
{
	t_mini	nyan;

	nyan.env = env;
	nyan.head = list_creator(cmd);
	return (nyan);
}
