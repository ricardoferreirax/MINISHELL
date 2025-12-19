/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:19:28 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/18 17:19:51 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->in_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

char	**init_mini(t_mini *nyan, char *cmd)
{
	char	**pipes;
	int		i;
	int		cmd_nbr;
	t_cmd	*prev;
	t_cmd	*curr;

	nyan->head = NULL;
	prev = NULL;
	pipes = split_ignore_quotes(cmd, '|', 0);
	if (!pipes)
		return (NULL);
	i = -1;
	cmd_nbr = arr_size((void **)pipes);
	while (++i < cmd_nbr)
	{
		curr = cmd_new();
		if (!curr)
			return (free_2d((void **)pipes), NULL);
		if (!nyan->head)
			nyan->head = curr;
		if (prev)
			prev->next = curr;
		prev = curr;
	}
	return (pipes);
}
