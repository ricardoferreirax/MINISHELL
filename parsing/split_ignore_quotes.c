/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ignore_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:16:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/02 12:22:26 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	count_words_ignore_quotes(char *str, char c)
{
	bool	inquote;
	bool	indquote;
	int		i;
	int		count;
	int		inword;

	i = -1;
	inword = false;
	count = 0;
	inquote = false;
	indquote = false;
	if (str == NULL)
		return (0);
	while (str[++i] != '\0')
	{
		update_quote_state(str[i], &inquote, &indquote);
		if (str[i] == c && (!inquote && !indquote))
			inword = false;
		else if (!inword)
		{
			inword = true;
			count++;
		}
	}
	return (count);
}

static char	*word_copy_ignorequotes(char **s, char c, int i)
{
	char	*dest;
	int		counter;
	bool	inquote;
	bool	indquote;

	inquote = false;
	indquote = false;
	counter = 0;
	while ((**s == c) && (**s != '\0'))
		(*s)++;
	while ((((**s != c) || inquote || indquote) && (**s != '\0')))
	{
		counter++;
		update_quote_state(**s, &inquote, &indquote);
		(*s)++;
	}
	dest = malloc(sizeof(char) * (counter + 2));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, ((*s) - counter), counter + 1);
	if (i == 1)
		dest[counter + 1] = '\1';
	else
		dest[counter + 1] = '\0';
	return (dest);
}

char	**split_ignore_quotes(char *str, char c, int k)
{
	int		i;
	char	**arr;
	int		wordnbr;

	i = 0;
	wordnbr = count_words_ignore_quotes(str, c);
	arr = malloc(sizeof(char *) * (wordnbr + 1));
	if (!arr)
		return (NULL);
	while (i < wordnbr)
	{
		arr[i] = word_copy_ignorequotes(&str, c, k);
		if (arr[i] == NULL)
			return (free_2d((void **)arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
