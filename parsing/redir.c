/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:48:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:48:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/parsing.h"

static bool	had_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
		i++;
	if (str[i + 1] == '\2')
		return (true);
	return (false);
}

static void	ambigous_redir(char *arg)
{
	ft_printf("Ambiguous redirection,");
	ft_printf(" where should i put this \"%s\"?\n", arg);
}

static t_redir	*redir_new(t_redir_type redir_type, char *arg)
{
	t_redir	*redir;

	if (!arg)
		return (NULL);
	redir = (t_redir *)calloc(1, sizeof(*redir));
	if (!redir)
		return (NULL);
	redir->type = redir_type;
	redir->next = NULL;
	if (redir_type == REDIR_HEREDOC)
	{
		redir->delimiter = ft_strdup(arg);
		if (!redir->delimiter)
			return (free(redir), NULL);
		redir->expansion = !had_quotes(arg);
		return (redir);
	}
	if (been_expanded(arg))
		return (free(redir), ambigous_redir(arg), NULL);
	redir->file = ft_strdup(arg);
	if (!redir->file)
		return (free(redir), NULL);
	return (redir);
}

int	redir_append(t_cmd *cmd, t_redir_type redir_type, char *arg)
{
	t_redir	*new_redir;
	t_redir	*last;

	if (!cmd || !arg)
		return (-1);
	new_redir = redir_new(redir_type, arg);
	if (!new_redir)
		return (-1);
	if (!cmd->redirs)
	{
		cmd->redirs = new_redir;
		return (0);
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = new_redir;
	return (0);
}
