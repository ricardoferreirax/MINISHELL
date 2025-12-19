/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:29:59 by pfreire-          #+#    #+#             */
/*   Updated: 2025/11/28 14:36:37 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	been_expanded(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (str[i + 1] == '\1')
		return (true);
	else
		return (false);
}

void	remove_placeholder(char *s)
{
	char	*read;
	char	*write;

	read = s;
	write = s;
	while (*read)
	{
		if (*read != '\1')
		{
			*write = *read;
			write++;
		}
		read++;
	}
	*write++ = '\0';
	if (*(read + 1) == '\0')
		*write = '\0';
	else if (*(read + 1) == '\2')
		*write = '\2';
	else
		*write = '\1';
}

bool	has_placeholder(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '\1')
			return (true);
		i++;
	}
	return (false);
}

static void	helper(char *c, bool *inquote, bool *indquote)
{
	if (*c == '\'' && !(*indquote))
	{
		*c = '\1';
		*inquote = !(*inquote);
	}
	else if (*c == '\"' && !(*inquote))
	{
		*c = '\1';
		*indquote = !(*indquote);
	}
}

char	**remove_quotes(char **arr)
{
	int		i;
	int		j;
	bool	inquote;
	bool	indquote;

	i = -1;
	while (arr[++i])
	{
		if (!been_expanded(arr[i]))
		{
			j = 0;
			inquote = false;
			indquote = false;
			while (arr[i][j] != '\0')
			{
				helper(&arr[i][j], &inquote, &indquote);
				j++;
			}
			if (i > 0 && has_placeholder(arr[i]) && sneaky_strcmp(arr[i - 1],
					"<<"))
				arr[i][j + 1] = '\2';
			remove_placeholder(arr[i]);
		}
	}
	return (arr);
}
