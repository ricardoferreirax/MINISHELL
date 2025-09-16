/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:08:08 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/16 14:25:53 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_words_ignore_quotes(char *str, char c)
{
	bool	inquote;
	bool	indquote;
	int		i;
	int		count;
	int		inword;

	i = 0;
	inword = false;
	count = 0;
	inquote = false;
	indquote = false;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			inquote = !inquote;
		if (str[i] == '\"')
			indquote = !indquote;
		if (str[i] == c && (!inquote || !indquote))
			inword = false;
		else if (!inword)
		{
			inword = true;
			count++;
		}
		i++;
	}
	return (count);
}

char	*word_copy_ignorequotes(char **s, char c)
{
	char	*dest;
	int		counter;
	bool	inquote = false;
	bool	indquote = false;

	counter = 0;
	while ((**s == c) && (**s != '\0'))
		(*s)++;
	while ((((**s != c) && (!inquote || !indquote)) && (**s != '\0')))
	{
		counter++;
		if ((**s) == '\'')
			inquote = !inquote;
		if ((**s) == '\"')
			indquote = !indquote;
		(*s)++;
	}
	dest = malloc(sizeof(char) * (counter + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, ((*s) - counter), counter + 1);
	return (dest);
}

char	**split_ignore_quotes(char *str, char c)
{
	int i = 0;
	char **arr;
	int wordnbr = count_words_ignore_quotes(str, c);
	arr = malloc(sizeof(char *) * (wordnbr + 1));
	if (!arr)
		return (NULL);
	while (i < wordnbr)
	{
		arr[i] = word_copy_ignorequotes(&str, c);
		if(arr[i] == NULL)
			return(free_chararr(arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return(arr);
}
