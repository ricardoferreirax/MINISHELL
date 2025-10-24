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

//char	*str_expand(char *str, t_envyan env)
//{
//	int		i;
//	int		size;
//	char	*dest;
//	// need to alocate enough memory for the var_name;
//	char	*var_name = NULL;
//	int		j;
//
//	i = 0;
//	size = 0;
//	while (str[i] != '\0')
//	{
//		if (str[i] == '$')
//		{
//			if (str[i + 1] == '?')
//			{
//			}
//			else
//			{
//				i++;
//				j = 0;
//				while (ft_isalpha(str[i + j]) || ft_isdigit(str[i + j]) || str[i
//					+ j] == '_')
//						j++;
//				var_name = malloc(sizeof(char) * j);
//			}
//		}
//		size++;
//	}
//	return (dest);
//}
//// below it is wrong. it doesn't hangel echo h$USER where the ouput is hpedro or echo h"ello" where the output is hello
//char	**expanser(t_cmd *cmd, t_envyan *envyan)
//{
//	int		i;
//	bool	inquote;
//	int		j;
//
//	while (cmd)
//	{
//		i = 0;
//		while (cmd->args[i] != NULL)
//		{
//			j = 0;
//			if (cmd->args[i][j] == '\'')
//				inquote = !inquote;
//			while (cmd->args[i][j] != '\0')
//			{
//				if (cmd->args[i][j] == '$')
//				{
//					// copy everything after $ and pass it to a function to return the desired string
//					// then copy everything to the cmd->args
//				}
//			}
//		}
//	}
//}

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
			if ((!inquote && !indquote) && (pipe[i] != ' ' && pipe[i] != '>' && pipe[i] != '<'))
			{
				dest[j + i] = ' ';
				j++;
			}
			continue;
		}
		dest[i + j] = pipe[i];
		i++;
	}
	dest[i + j] = '\0';
	ft_printf("%s \n", dest);
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
			// ft_printf("token n%d : %s\n", j, tokens[j]);
			if (!parse(curr, tokens, &j))
				break ;
			// j++;
		}
		curr = curr->next;
		i++;
	}
	// expnade HERE and do it with the list mf
	//expanser(curr, nyan->envyan);
}
