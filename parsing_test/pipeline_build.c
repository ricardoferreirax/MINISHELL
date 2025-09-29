/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 15:10:09 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/parsing.h"

t_cmd	*cmd_new(void);
int		arr_size(void **arr);

char	**init_mini(t_mini *nyan, char *cmd)
{
	char	**pipes;
	int		i;
	int		cmd_nbr;
	t_cmd	*prev;
	t_cmd	*curr;

	nyan->head = NULL;
	prev = NULL;
	pipes = split_ignore_quotes(cmd, '|');
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


int normalize_str(char *str)
{
	int i = 0;
	int size = ft_strlen(str);
	while(str[i] != '\0')
	{
		if(str[i] == '>' || str[i] == '<')
		{
			if(i > 0 && str[i - 1] != ' ')
				size++;
			if(str[i + 1] != '<' && str[i + 1] != '>' && str[i + 1] != ' ')
				size++;
		}
		i++;
	}
}


char **pre_parse(char *pipe)
{
	int i = 0;
	int j = 0;
	char **dest;
	char *temp;
	temp = malloc(sizeof(char) * normalize_str(pipe));
	while(pipe[i] != '\0')
	{
		if(pipe[i] == '<' || pipe[i] == '>')
		{
			if(i > 0 && pipe[i - 1] != ' ')
			{
				temp[i + j] = ' ';
				j++;
			}
			// Be careful to handle >< or <>
			if(pipe[i + 1] != '<' && pipe[i + 1] != '>' && pipe[i + 1] != ' ')
			{
				temp[i + j] = pipe[i];
				temp[i + j] = ' ';
				j++;
				i++;
				continue;
			}
		}
		temp[i + j] = pipe[i];
	}
}

void	fill_mini(t_mini *nyan, char **pipes)
{
	int		i;
	t_cmd	*curr;
	char	**tokens;

	curr = nyan->head;
	i = 0;
	while (pipes && pipes[i] && curr)
	{
		tokens = split_ignore_quotes(pipes[i], ' ');
		if (tokens)
		{
			fill_subcmd(curr, tokens);
			free_2d((void **)tokens);
		}
		curr = curr->next;
		i++;
	}
}
