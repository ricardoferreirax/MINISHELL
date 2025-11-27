/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fill_mini.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/04 14:10:17 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>

int		arr_size(void **arr);

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->in_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

char	**init_mini(t_mini *nyan, char *cmd)
{
	char	**pipes;
	int		i;
	int		cmd_nbr;
	t_cmd	*prev;
	t_cmd	*curr;

	nyan->head = NULL;
	prev = NULL;
	pipes = split_ignore_quotes(cmd, '|', 0);
	if (!pipes)
		return (NULL);
	i = 0;
	cmd_nbr = arr_size((void **)pipes);
	while (i < cmd_nbr)
	{
		curr = cmd_new();
		if (!curr)
			break ;
		if (!nyan->head)
			nyan->head = curr;
		if (prev)
			prev->next = curr;
		prev = curr;
		i++;
	}
	return (pipes);
}

int	add_spaces_size_count(char *str)
{
	int		i;
	int		size;
	bool	inquote;
	bool	indquote;

	i = 0;
	size = 0;
	inquote = false;
	indquote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (str[i] == '<' || str[i] == '>')
		{
			if ((!indquote && !indquote) && (str[i - 1] != ' ' || str[i
					- 1] != '>' || str[i - 1] != '<'))
				size++;
			if ((!indquote && !inquote) && (str[i + 1] != ' ' || str[i
					+ 1] != '>' || str[i + 1] != '<'))
				size++;
		}
		i++;
		size++;
	}
	return (size);
}

char	*find_expanded(char *cmd_args, t_envyan *envyan, int lst_status)
{
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	temp = malloc(sizeof(char) * ft_strlen(cmd_args) + 1);
	if (!temp)
		return (NULL);
	if (strcmp(cmd_args, "$?") == 0)
		return (ft_itoa(lst_status));
	cmd_args++;
	while (cmd_args[i] != '\0' && ((cmd_args[i] >= 'a' && cmd_args[i] <= 'z')
			|| (cmd_args[i] >= 'A' && cmd_args[i] <= 'Z')
			|| (cmd_args[i] == '_')))
	{
		temp[i] = cmd_args[i];
		i++;
	}
	temp[i] = '\0';
	result = NULL;
	while (envyan)
	{
		if (ft_strcmp(temp, envyan->key) == 0)
		{
			if (result)
				free(result);
			result = ft_strdup(envyan->value);
			break ;
		}
		envyan = envyan->next;
	}
	free(temp);
	return (result);
}

char	*insert_expanded(char *args, int j, char *expanded)
{
	size_t	i;
	int		skip_len;
	char	*result;
	size_t	k;
	size_t	e;

	i = 0;
	skip_len = 1;
	result = malloc(sizeof(char) * (ft_strlen(args) + ft_strlen(expanded) + 3));
	if (!result)
		return (NULL);
	while (args[j + skip_len] != '\0' && ((args[j + skip_len] >= 'a' && args[j
				+ skip_len] <= 'z') || (args[j + skip_len] >= 'A' && args[j
				+ skip_len] <= 'Z') || args[j + skip_len] == '_'
			|| (skip_len == 1 && args[j + skip_len] == '?')))
		skip_len++;
	k = 0;
	while (k < (size_t)j)
	{
		result[i] = args[k];
		i++;
		k++;
	}
	e = 0;
	while (e < ft_strlen(expanded))
	{
		result[i] = expanded[e];
		i++;
		e++;
	}
	k += skip_len;
	while (k < ft_strlen(args))
	{
		result[i] = args[k];
		i++;
		k++;
	}
	result[i] = '\0';
	result[i + 1] = '\0';
	return (result);
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
	*write = '\0';
}

int	expanser(char **final, t_envyan *env, int status)
{
	char	*temp;
	char	*expanded;
	int		i;
	bool	inquote;
	bool	indquote;
	int		k;

	i = 0;
	inquote = false;
	indquote = false;
	while (final[i])
	{
		k = 0;
		while (final[i][k] != '\0')
		{
			if (final[i][k] == '\'' && !indquote)
			{
				inquote = !inquote;
			}
			if (final[i][k] == '\"' && !inquote)
			{
				indquote = !indquote;
			}
			if (final[i][k] == '$' && !inquote)
			{
				expanded = find_expanded(final[i] + k, env, status);
				temp = insert_expanded(final[i], k, expanded);
				free(final[i]);
				final[i] = ft_strdup(temp);
			}
			k++;
		}
		i++;
	}
	return (0);
}

char	**add_spaces(char *pipe)
{
	int		i;
	char	*dest;
	bool	indquote;
	bool	inquote;
	char	**final;
	int		j;

	i = 0;
	indquote = false;
	inquote = false;
	j = 0;
	dest = malloc(sizeof(char) * add_spaces_size_count(pipe) + 2);
	if (!dest)
		return (NULL);
	while (pipe[i])
	{
		if (pipe[i] == '\'' && !indquote)
			inquote = !inquote;
		if (pipe[i] == '\"' && !inquote)
			indquote = !indquote;
		if (pipe[i] == '<' || pipe[i] == '>')
		{
			if ((!inquote && !indquote) && (pipe[i - 1] != ' ' && pipe[i
					- 1] != '>' && pipe[i - 1] != '<'))
			{
				dest[j + i] = ' ';
				j++;
			}
			dest[j + i] = pipe[i];
			i++;
			if ((!inquote && !indquote) && (pipe[i] != ' ' && pipe[i] != '>'
					&& pipe[i] != '<'))
			{
				dest[j + i] = ' ';
				j++;
			}
			continue ;
		}
		dest[i + j] = pipe[i];
		i++;
	}
	dest[i + j] = '\0';
	dest[i + j + 1] = '\0';
	final = split_ignore_quotes(dest, ' ', 0);
	free(dest);
	return (final);
}

void	print2darr(char **txt)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		printf("%d: %s\n", i + 1, txt[i]);
		i++;
	}
}
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
		else if(s[j + 1] == '\1')
			ft_printf("\\0\\1");
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

	joined = malloc(sizeof(char *) - (arr_size((void **)s1)
				* arr_size((void **)s2)));
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

char	**retokenize(char **tokens)
{
	char	**retokens;
	int		word_count = 0;
	int		i;
	int rtk_increment = 0;

	i = 0;
	while (tokens[i])
	{
		word_count += count_words_ignore_quotes(tokens[i], ' ');
		i++;
	}
	retokens = malloc(sizeof(char *) * (word_count + 1));
	i = 0;
	while(tokens[i])
	{
		if(count_words_ignore_quotes(tokens[i], ' ') == 1)
		{
			int k = 0;
			retokens[rtk_increment] = malloc(sizeof(char) * (ft_strlen(tokens[i]) + 2));
			while(tokens[i][k] != '\0')
			{
				retokens[rtk_increment][k] = tokens[i][k];
				k++;
			}
			retokens[rtk_increment][k] = '\0';
			retokens[rtk_increment][k + 1] = '\0';
			rtk_increment++;
		}
		else
		{
			char **temp = split_ignore_quotes(tokens[i], ' ', 1);
			int k = 0;
			while(temp[k])
			{
				int l = 0;
				retokens[rtk_increment] = malloc(sizeof(char) * (ft_strlen(temp[k]) + 2));
				while(temp[k][l] != '\0')
				{
					retokens[rtk_increment][l] = temp[k][l];
					l++;
				}
				retokens[rtk_increment][l] = '\0';
				retokens[rtk_increment][l + 1] = '\1';
				rtk_increment++;
				k++;
			}
		}
		i++;
	}
	retokens[rtk_increment] = NULL;
	return (retokens);
}
char **remove_quote(char **arr)
{
	int i = 0;
	while(arr[i])
	{
		int j = 0;
		bool inquote = false;
		bool indquote = false;
		while(arr[i][j] != '\0')
		{
			if(arr[i][j] == '\'' && !indquote)
			{
				arr[i][j] = '\1';
				inquote = !inquote;
			}
			if(arr[i][j] == '\"' && !inquote)
			{
				arr[i][j] = '\1';
				indquote = !indquote;
			}
			j++;
		}
		remove_placeholder(arr[i]);
		i++;
	}
	return arr;
}

int	fill_mini(t_mini *nyan, char **pipes)
{
	int		i;
	t_cmd	*curr;
	char	**tokens;
	char	**retokens;
	int		j;

	curr = nyan->head;
	i = 0;
	while (pipes && pipes[i] && curr)
	{
		tokens = add_spaces(pipes[i]);
		if (!tokens)
		{
			i++;
			free_2d((void **)tokens);
		}
		expanser(tokens, nyan->envyan, nyan->last_status);
		retokens = retokenize(tokens);
		tokens = remove_quote(retokens);
		// print2darr(retokens);
		print_arr(retokens);
		j = 0;
		if(!retokens)
			printf("you're stupid\n"), exit(-1);
		while (retokens[j] != NULL)
		{
			if (!parse(curr, retokens, &j))
				break ;
		}
		curr = curr->next;
		i++;
	}
	curr = nyan->head;
	return (0);
}
