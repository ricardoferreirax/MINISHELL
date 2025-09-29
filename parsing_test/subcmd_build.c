/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcmd_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:56:45 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 15:27:14 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/parsing.h"

static t_subcmd	*subcmd_new(void)
		// cria um subcomando (um comando com os args e com a lista de redirs)
{
	t_subcmd	*subcmd;

	subcmd = (t_subcmd *)calloc(1, sizeof(*subcmd));
	if (!subcmd)
		return (NULL);
	subcmd->args = NULL;
	subcmd->cmd = NULL;
	subcmd->delimiter = NULL;
	subcmd->outfile = NULL;
	subcmd->infile = NULL;
	subcmd->in_fd = -1;
	subcmd->out_fd = -1;
	subcmd->next = NULL; /* 1 subcmd por t_cmd */
	return (subcmd);
}

int	add_arg(t_subcmd *subcmd, const char *token)
{
	int		count;
	int		i;
	char	**new_arg;

	if (!subcmd || !token)
		return (1);
	count = 0;
	if (subcmd->args)
	{
		while (subcmd->args[count])
			count++;
	}
	new_arg = (char **)malloc((count + 2) * sizeof(char *));
	if (!new_arg)
		return (1);
	i = 0;
	while (i < count) // copia osponteiros antigos
	{
		new_arg[i] = subcmd->args[i];
		i++;
	}
	new_arg[count] = ft_strdup(token);
	if (!new_arg[count])
	{
		free(new_arg);
		return (1);
	}
	new_arg[count + 1] = NULL;
	if (subcmd->args)
		free(subcmd->args);
	subcmd->args = new_arg;
	if (!subcmd->cmd)
	{
		subcmd->cmd = ft_strdup(token);
		if (!subcmd->cmd)
			return (1);
	}
	return (0);
}

void	fill_subcmd(t_cmd *node, char **tokens)
{
	t_subcmd	*sub;
	int			i;

	sub = subcmd_new();
	if (!sub)
		return ;
	i = 0;
	while (tokens[i])
	{
		if (!parse(sub, tokens, &i))
			break ;
	}
	node->head = sub;
}
