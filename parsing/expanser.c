/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:21:04 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/19 17:42:34 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "MiNyanShell.h"
#include "strings/ft_strings.h"

char	*ft_strdup_with_ending(char *str, int c)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	dup[i + 1] = (char)c;
	return (dup);
}

static void	helper_helper(char **final, t_envyan *env, int status)
{
	int		k;
	char	*expanded;
	char	*temp;
	bool	quotes[2];

	k = 0;
	quotes[0] = false;
	quotes[1] = false;
	while (*final && (*final)[k] != '\0')
	{
		update_quote_state((*final)[k], &quotes[0], &quotes[1]);
		if ((*final)[k] == '$' && !quotes[0])
		{
			expanded = find_expanded(*final + k, env, status);
			temp = insert_expanded(*final, k, expanded);
			if (expanded)
				free(expanded);
			free(*final);
			(*final) = ft_strdup_with_ending(temp, 2);
			if (temp)
				free(temp);
			continue ;
		}
		k++;
	}
}

int	expanser(char **final, t_envyan *env, int status)
{
	int	i;

	i = 0;
	if (!final)
		return (-1);
	while (final[i])
	{
		if (i > 0 && ft_strcmp(final[i - 1], "<<") == 0)
		{
			i++;
			continue ;
		}
		helper_helper(&final[i], env, status);
		i++;
	}
	return (0);
}
