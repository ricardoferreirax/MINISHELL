/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:02:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/25 12:31:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return 0;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    while (*s)
    {
        write(fd, s, 1);
        s++;
    }
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len])
        len++;
    return len;
}


char *ft_strdup(const char *s1)
{
    char *dup;
    int len = ft_strlen(s1);
    int i;

    dup = (char *)malloc((len + 1) * sizeof(char));
    if (!dup)
        return NULL;
    i = 0;
    while (s1[i])
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	idx;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	idx = 0;
	while (idx < len)
		substring[idx++] = s[start++];
	substring[idx] = '\0';
	return (substring);
}

static void	quote_check(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == c)
			*quote = 0;
		else if (*quote == 0)
			*quote = c;
	}
}

static int	count_words(const char *s, char sep)
{
	int		i;
	int		count;
	int		in_word;
	char	quote;

	i = 0;
	count = 0;
	in_word = 0;
	quote = 0;
	while (s[i] != '\0')
	{
		quote_check(s[i], &quote);
		if ((s[i] != sep || quote) && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		if (s[i] == sep && !quote)
			in_word = 0;
		i++;
	}
	return (count);
}

static void	free_all(char **arr, int size)
{
	while (size >= 0)
	{
		free(arr[size]);
		size--;
	}
	free(arr);
}

static int	fill_word_array(char **arr, char const *s, char c)
{
	int		i;
	int		len;
	int		start;
	char	delimiter;

	i = 0;
	start = 0;
	while (i < count_words(s, c))
	{
		delimiter = c;
		while (s[start] == c)
			start++;
		if (s[start] == '\'' || s[start] == '\"')
			delimiter = s[start++];
		len = 0;
		while (s[start + len] && s[start + len] != delimiter)
			len++;
		arr[i] = ft_substr(s, start, len);
		if (!arr[i])
			return (free_all(arr, i - 1), 0);
		start += len + 1;
		i++;
	}
	arr[i] = NULL;
	return (1);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**strings;

	strings = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	if (!fill_word_array(strings, s, c))
		return (NULL);
	return (strings);
}