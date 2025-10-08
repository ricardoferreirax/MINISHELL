/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:50:57 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 17:11:11 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redirs(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		if (r->file)
			free(r->file);
		if (r->delimiter)
			free(r->delimiter);
		free(r);
		r = next;
	}
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		if (cur->in_fd != -1)
		{
			close(cur->in_fd);
			cur->in_fd = -1;
		}
		free_argv(cur->args);
		free_redirs(cur->redirs);
		free(cur);
		cur = next;
	}
}
