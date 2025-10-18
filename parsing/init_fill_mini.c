/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fill_mini.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:29:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/09 10:52:25 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int		arr_size(void **arr);

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)calloc(1, sizeof(*cmd));
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

int	expand_size(char *str, int i)
{
	// must return the size of the expanded string $XXXX
	(void)str;
	return (i - i);
}

int	pre_parse_size_count(char *str)
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
		if (!inquote && str[i] == '$')
			size += expand_size(str, i);
		i++;
		size++;
	}
	return (size);
}

char	*expander_helper(char *str, t_envyan *envyan)
{
	char	*expanded;

	while (envyan != NULL)
	{
		if (ft_strcmp(envyan->key, str) == 0)
		{
			expanded = ft_strdup(envyan->value);
			return (expanded);
		}
		envyan = envyan->next;
	}
	expanded = ft_strdup("");
	return (expanded);
}

char	**expanser(char *str, t_envyan *envyan)
{
	char	**out;
	int		i;
	char	*temp;

	out = split_ignore_quotes(str, ' ');
	i = 0;
	while (out[i] != NULL)
	{
		if (out[i][0] == '$')
		{
			temp = ft_strdup(out[i]);
			free(out);
			out[i] = expander_helper(temp, envyan);
			if (strcmp(out[i], (void *)1))
			{
				// what should i do?
			}
		}
		i++;
	}
	return (out);
}

char	**pre_parse(char *pipe, t_envyan envyan)
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
	dest = malloc(sizeof(char *) * pre_parse_size_count(pipe) + 1);
	// printf("Size of pipe: %d\n", pre_parse_size_count(pipe));
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
			if ((!inquote && !indquote) && (pipe[i + 1] != ' ' && pipe[i
					+ 1] != '>' && pipe[i + 1] != '<'))
			{
				dest[j + i] = ' ';
				j++;
			}
		}
		if (!inquote && pipe[i] == '$')
		{
			// must copy the expanded string $XXXX
			j += ft_strlcat(dest, dest, 100);
		}
		dest[i + j] = pipe[i];
		i++;
	}
	dest[i + j] = '\0';
	printf("dest before split: %s\n", dest);
	final = expanser(dest, &envyan);
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
		tokens = pre_parse(pipes[i], *nyan->envyan);
		// tokens = split_ignore_quotes(pipes[i], ' ');
		j = 0;
		while (tokens[j] != NULL)
		{
			// ft_printf("token n%d : %s\n", j, tokens[j]);
			if (!parse(curr, tokens, &j))
				break ;
			// j++;
		}
		curr = curr->next;
		i++;
	}
}
