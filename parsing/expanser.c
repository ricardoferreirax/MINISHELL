/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:21:04 by pfreire-          #+#    #+#             */
/*   Updated: 2025/11/28 14:35:52 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*ft_strdup_with_ending(char *str)
{
	char	*dup;
	int		i;

	if(!str)
		return NULL;
	dup = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if(!dup)
		return NULL;
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	dup[i + 1] = '\1';
	return (dup);
}

char	*find_expanded(char *cmd_args, t_envyan *envyan, int lst_status)
{
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	if(!cmd_args)
		return(ft_strdup(""));
	cmd_args++;
	if(cmd_args[0] == '?')
		return(ft_itoa(lst_status));
	if(cmd_args[0] == '0')
		return(ft_strdup("MiNyanShell nyan~ :3"));
	if(ft_isdigit(cmd_args[0]))
		return(ft_strdup(""));
	temp = malloc(sizeof(char) * ft_strlen(cmd_args) + 1);
	if (!temp)
		return(ft_strdup(""));
	while (cmd_args[i] != '\0' && (ft_isalpha(cmd_args[i]) || (cmd_args[i] == '_')))
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
	if(!result)
		return(ft_strdup(""));
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
	if(!expanded)
		return NULL;
	result = malloc(sizeof(char) * (ft_strlen(args) + ft_strlen(expanded) + 3));
	if (!result)
		return (NULL);
	while (args[j + skip_len] != '\0' && (ft_isalpha(args[j + skip_len]) || args[j + skip_len] == '_'))
		skip_len++;
	if((skip_len == 1 && ((args[j + skip_len] == '?' || ft_isdigit(args[j + skip_len])))))
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
	// if(is_redir(expanded))
	// 	result[i + 1] = '\2';
	// else
	result[i + 1] = '\0';
	return (result);
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
		if(i > 0 && ft_strcmp(final[i - 1], "<<") == 0)
		{
			i++;
			continue;
		}
		k = 0;
		while (final[i] && final[i][k] != '\0')
		{
			if (final[i][k] == '\'' && !indquote)
				inquote = !inquote;
			if (final[i][k] == '\"' && !inquote)
				indquote = !indquote;
			if (final[i][k] == '$' && !inquote)
			{
				expanded = find_expanded(final[i] + k, env, status);
				temp = insert_expanded(final[i], k, expanded);
				free(expanded);
				free(final[i]);
				final[i] = ft_strdup_with_ending(temp);
				free(temp);
				if(!final[i])
					return -1;
			}
			else
				k++;
		}
		i++;
	}
	return (0);
}
