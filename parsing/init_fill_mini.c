/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fill_mini.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/02 12:31:59 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include <stddef.h>
#include <string.h>

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

char	*find_expanded(char *cmd_args, t_envyan *envyan)
{
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	temp = malloc(sizeof(char) * ft_strlen(cmd_args) + 1);
	result = ft_strdup("");
	cmd_args++;
	while (cmd_args[i] != '\0' && ((cmd_args[i] >= 'a' && cmd_args[i] <= 'z') || (cmd_args[i] >= 'A'
			&& cmd_args[i] <= 'Z') || (cmd_args[i] == '_')))
	{
		temp[i] = cmd_args[i];
		i++;
	}
	temp[i] = '\0';
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
	return (result);
}

char *insert_expanded(char *args, int j, char *expanded)
{
	size_t i = 0;
	int skip_len = 1;
	while(args[j + skip_len] != '\0' && ((args[j + skip_len] >= 'a' && args[j + skip_len] <= 'z') || (args[j + skip_len] >= 'A' && args[j + skip_len] <= 'Z') || args[j + skip_len] == '_'))
		skip_len++;
	char *result = malloc(sizeof(char) * (ft_strlen(args) + ft_strlen(expanded) + 2));
	size_t k = 0;
	while(k < (size_t)j)
	{
		result[i] = args[k];
		i++;
		k++;
	}
	size_t e = 0;
	while(e < ft_strlen(expanded))
	{
		result[i] = expanded[e];
		i++;
		e++;
	}
	k += skip_len;
	while(k < ft_strlen(args))
	{
		result[i] = args[k];
		i++;
		k++;
	}
	result[i] = '\0';
	return result;
}


void expanser(t_cmd *cmd, t_envyan *envyan)
{
	int		i;
	bool	inquote;
	bool	indquote;
	int		j;
	char	*expanded;
	char *temp;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			j = 0;
			inquote = false;
			indquote = false;
			while (cmd->args[i][j] != '\0')
			{
				if (cmd->args[i][j] == '\'' && !indquote)
					inquote = !inquote;
				if(cmd->args[i][j] == '\"' && !indquote)
					indquote = !indquote;
				if (cmd->args[i][j] == '$' && !inquote)
				{
					expanded = find_expanded(cmd->args[i] + j, envyan);
					temp = insert_expanded(cmd->args[i], j, expanded);
					free(cmd->args[i]);
					cmd->args[i] = ft_strdup(temp);
					j--;
				}
				j++;
			}
			i++;
		}
		cmd = cmd->next;
	}
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
	dest = malloc(sizeof(char) * add_spaces_size_count(pipe) + 1);
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
	final = split_ignore_quotes(dest, ' ');
	free(dest);
	return (final);
}

void	fill_mini(t_mini *nyan, char **pipes)
{
	int		i;
	t_cmd	*curr;
	char	**tokens;
	int		j;

	curr = nyan->head;
	i = 0;
	while (pipes && pipes[i] && curr)
	{
		tokens = add_spaces(pipes[i]);
		j = 0;
		while (tokens[j] != NULL)
		{
			if (!parse(curr, tokens, &j))
				break ;
		}
		curr = curr->next;
		i++;
	}
	curr = nyan->head;
	expanser(curr, nyan->envyan);
}
