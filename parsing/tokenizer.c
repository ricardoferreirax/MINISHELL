/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:40:33 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/18 20:40:36 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	count_total_words(char **tokens, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (tokens[i])
	{
		word_count += count_words_ignore_quotes(tokens[i], c);
		i++;
	}
	return (word_count);
}

static int	single_word(char **retokens, char *tokens, int *idx)
{
	char	marker;

	marker = '\0';
	if (is_redir(tokens) && been_expanded(tokens))
		marker = '\2';
	retokens[*idx] = ft_strdup_with_ending(tokens, marker);
	if (!retokens[*idx])
		return (-1);
	(*idx)++;
	return (0);
}

static int	multi_word(char **retokens, char *tokens, int *idx)
{
	char	**temp;
	int		k;

	temp = split_ignore_quotes(tokens, ' ', 1);
	if (!temp)
		return (-1);
	k = 0;
	while (temp[k])
	{
		retokens[*idx] = ft_strdup_with_ending(temp[k], '\1');
		if (!retokens[*idx])
			return (free_2d((void **)temp), -1);
		(*idx)++;
		k++;
	}
	free_2d((void **)temp);
	return (0);
}

char	**retokenize(char **tokens)
{
	char	**retokens;
	int		word_count;
	int		i;
	int		rtk_increment;

	rtk_increment = 0;
	if (!tokens)
		return (NULL);
	word_count = count_total_words(tokens, ' ');
	retokens = malloc(sizeof(char *) * (word_count + 1));
	if (!retokens)
		return (NULL);
	i = -1;
	while (tokens[++i])
	{
		if (count_words_ignore_quotes(tokens[i], ' ') == 1)
		{
			if (single_word(retokens, tokens[i], &rtk_increment))
				return (free_2d((void **)retokens), NULL);
		}
		else if (multi_word(retokens, tokens[i], &rtk_increment))
			return (free_2d((void **)retokens), NULL);
	}
	retokens[rtk_increment] = NULL;
	return (retokens);
}

char	**tokenizer(char *pipe, t_envyan *env, int status)
{
	char	**tokens;
	char	**retokens;

	tokens = add_spaces(pipe);
	if (!tokens)
		return (NULL);
	if (expanser(tokens, env, status))
		return (free_2d((void **)tokens), NULL);
	retokens = retokenize(tokens);
	free_2d((void **)tokens);
	if (!retokens)
		return (NULL);
	tokens = remove_quotes(retokens);
	return (tokens);
}
