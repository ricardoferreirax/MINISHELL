/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/14 15:00:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "memory/memory.h"
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
		{
			if(pipes)
				free_2d((void **)pipes);
			return(NULL) ;
		}
		if (!nyan->head)
			nyan->head = curr;
		if (prev)
			prev->next = curr;
		prev = curr;
		i++;
	}
	return (pipes);
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

	joined = malloc(sizeof(char *) - (arr_size((void **)s1)
				* arr_size((void **)s2)));
	if(!joined)
		return NULL;
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
	int		word_count;
	int		i;
	int		rtk_increment;
	int		k;
	char	**temp;
	int		l;

	word_count = 0;
	rtk_increment = 0;
	i = 0;
	while (tokens[i])
	{
		word_count += count_words_ignore_quotes(tokens[i], ' ');
		i++;
	}
	retokens = malloc(sizeof(char *) * (word_count + 1));
	if(!retokens)
		return NULL;
	i = 0;
	while (tokens[i])
	{
		if (count_words_ignore_quotes(tokens[i], ' ') == 1)
		{
			k = 0;
			retokens[rtk_increment] = malloc(sizeof(char)
					* (ft_strlen(tokens[i]) + 3));
			while (tokens[i][k] != '\0')
			{
				retokens[rtk_increment][k] = tokens[i][k];
				k++;
			}
			retokens[rtk_increment][k] = '\0';
			if(is_redir(tokens[i]) && been_expanded(tokens[i]))
				retokens[rtk_increment][k + 1] = '\2';
			else
				retokens[rtk_increment][k + 1] = '\0';
			rtk_increment++;
		}
		else
		{
			temp = split_ignore_quotes(tokens[i], ' ', 1);
			if(!temp)
			{
				if(tokens)
					free_2d((void **) tokens);
				return NULL;
			}
			k = 0;
			while (temp[k])
			{
				l = 0;
				retokens[rtk_increment] = malloc(sizeof(char)
						* (ft_strlen(temp[k]) + 2));
				if(!retokens[rtk_increment])
				{
					free_2d((void **)temp);
					free_2d((void **)retokens);
					return NULL;
				}
				while (temp[k][l] != '\0')
				{
					retokens[rtk_increment][l] = temp[k][l];
					l++;
				}
				retokens[rtk_increment][l] = '\0';
				retokens[rtk_increment][l + 1] = '\1';
				rtk_increment++;
				k++;
			}
			free_2d((void **)temp);
		}
		i++;
	}
	retokens[rtk_increment] = NULL;
	return (retokens);
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
			return(free_2d((void **)tokens), -1);
		if(expanser(tokens, nyan->envyan, nyan->last_status))
			return(free_2d((void **)tokens), -1);
		retokens = retokenize(tokens);
		free_2d((void **)tokens);
		if(!retokens)
			return (-1);
		tokens = remove_quotes(retokens);
		j = 0;
		while (tokens[j] != NULL)
		{
			if (parse(curr, tokens, &j))
			{
				ft_printf("NYAAAAN, a parsing error has occureded but i won't tell what it is nyan~ :3\n");
				return -1;
			}
		}
		free_2d((void **)tokens);
		curr = curr->next;
		i++;
	}
	curr = nyan->head;
	return (0);
}

