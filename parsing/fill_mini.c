/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:48:28 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "MiNyanShell.h"
#include "memory/memory.h"

void	print_arr(char **arr)
{
	int		i;
	char	*s;
	int		j;

	i = 0;
	while (arr[i])
	{
		s = arr[i];
		j = 0;
		while (s[j] != '\0')
		{
			ft_printf("%c", s[j]);
			j++;
		}
		if (s[j + 1] == '\0')
			ft_printf("\\0\\0");
		else if (s[j + 1] == '\1')
			ft_printf("\\0\\1");
		else if (s[j + 1] == '\2')
			ft_printf("\\0\\2");
		else
			ft_printf("*garbage data noises*");
		ft_printf("\n");
		i++;
	}
}

char	**arr_join(char **s1, char **s2)
{
	char	**joined;
	int		i;
	int		k;

	joined = malloc(sizeof(char *) * (arr_size((void **)s1)
				+ arr_size((void **)s2) + 1));
	if (!joined)
		return (NULL);
	if (!s1)
		return (s2);
	i = 0;
	while (s1[i])
	{
		joined[i] = ft_strdup(s1[i]);
		i++;
	}
	k = 0;
	while (s2[k])
	{
		joined[i + k] = ft_strdup(s2[k]);
		k++;
	}
	return (joined);
}

int	fill_mini(t_mini *nyan, char **pipes)
{
	int		i;
	t_cmd	*curr;
	char	**tokens;
	int		j;

	curr = nyan->head;
	i = 0;
	while (pipes && pipes[i] && curr)
	{
		tokens = tokenizer(pipes[i], nyan->envyan, nyan->last_status);
		if (!tokens)
			return (-1);
		j = 0;
		while (tokens[j] != NULL)
		{
			if (parse(curr, tokens, &j))
				return (ft_printf("A parsing error has occureded !\n"), -1);
		}
		free_2d((void **)tokens);
		curr = curr->next;
		i++;
	}
	curr = nyan->head;
	return (0);
}
