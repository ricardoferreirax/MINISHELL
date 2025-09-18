/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:08:08 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 16:01:46 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"
#include <stdbool.h>

char	*skip_whitespaces(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

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
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (str[i] == c && (!inquote && !indquote))
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
		if ((**s) == '\'' && !indquote)
			inquote = !inquote;
		else if ((**s) == '\"' && !inquote)
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
		arr[i] = word_copy_ignorequotes(&str, c);
		if (arr[i] == NULL)
			return (free_chararr(arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

bool	no_unclosed_quotes(char *str)
{
	bool	inquote;
	bool	indquote;
	int		i;

	inquote = false;
	indquote = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		i++;
	}
	if (indquote || inquote)
		return (false);
	return (true);
}

bool	forbidden_instruction(char *str, int i)
{
	if (str[i] == '&')
	{
		if (str[i + 1] == '&')
			return (true);
	}
	else if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			return (true);
	}
	else if (str[i] == '*')
	{
		return (true);
	}
	return (false);
}

bool	no_forbidden_actions(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	i = 0;
	inquote = false;
	indquote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (!forbidden_instruction(str, i) && !indquote && !inquote)
			return (false);
		i++;
	}
	return (true);
}

t_redir_type	which_type(t_subcmd *cmd, char **argv, int i)
{
	if (ft_strcmp(argv[i], "<<") == 0)
	{
		cmd->delimiter = ft_strdup(argv[i + 1]);
		return (REDIR_HEREDOC);
	}
	if (ft_strcmp(argv[i], ">>"))
	{
		cmd->outfile = ft_strdup(argv[i + 1]);
		return (REDIR_APPEND);
	}
	if (ft_strcmp(argv[i], "<"))
	{
		cmd->infile = ft_strdup(argv[i]);
		return (REDIR_IN);
	}
	if (ft_strcmp(argv[i], ">"))
	{
		cmd->outfile = argv[i + 1];
		return (REDIR_OUT);
	}
	return (REDIR_INVALID);
}

void	fill_arg(t_subcmd *cmd, char **argv, int *i)
{
	cmd->type = which_type(cmd, argv, *i);
	if (cmd->type != REDIR_INVALID)
		i++;
}
void	fill_subcmd(t_subcmd *cmd, char *args)
{
	int		i;
	char	**argv;

	i = 0;
	argv = split_ignore_quotes(args, ' ');
	while (argv[i] != NULL)
	{
		fill_arg(cmd, argv, &i);
		i++;
	}
}

t_subcmd	*new_subcmd(char *cmd, char *args)
{
	t_subcmd *sc = malloc(sizeof(t_subcmd));

	sc->cmd = ft_strdup(cmd);
	fill_subcmd(sc, args);
	return (sc);
}
