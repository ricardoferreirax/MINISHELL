/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:51:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:08:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"
#include "../include/execution.h"

static void	remove_envyan_key(t_mini *mini, char *key)
{
	t_envyan	*prev;
	t_envyan	*current;

	if (!mini || !key)
		return ;
	prev = NULL;
	current = mini->envyan;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				mini->envyan = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_cmd *cmd, t_mini *mini)
{
	int	i;

	if (!cmd || !cmd->args || !mini)
		return (1);
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
			remove_envyan_key(mini, cmd->args[i]);
		i++;
	}
	return (0);
}
