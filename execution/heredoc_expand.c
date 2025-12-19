/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:45:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:46:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"
#include "parsing.h"
#include <string.h>

static int	dolar_pos(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '$')
		i++;
	return (i);
}

static int	count_ma_money_babyyy(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

static int	expand_one_dollar(char **line, t_mini *mini)
{
	int		dolar_index;
	char	*expanded;
	char	*temp;

	dolar_index = dolar_pos(*line);
	expanded = find_expanded(*line + dolar_index, mini->envyan,
			mini->last_status);
	if (!expanded)
		return (-1);
	temp = insert_expanded(*line, dolar_index, expanded);
	free(expanded);
	free(*line);
	if (!temp)
		return (-1);
	*line = ft_strdup_with_ending(temp, 2);
	free(temp);
	if (!*line)
		return (-1);
	return (0);
}

int	expand_heredoc_line(char **line, t_redir *redir, t_mini *mini)
{
	int	i;
	int	dolar_count;

	if (!redir->expansion)
		return (0);
	i = 0;
	dolar_count = count_ma_money_babyyy(*line);
	while (i < dolar_count)
	{
		if (expand_one_dollar(line, mini) != 0)
			return (-1);
		i++;
	}
	return (0);
}
