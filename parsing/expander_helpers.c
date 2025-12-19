/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:38:35 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/19 17:40:43 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static char	*helper(t_envyan *env, char *temp)
{
	while (env)
	{
		if (ft_strcmp(temp, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*find_expanded(char *cmd_args, t_envyan *envyan, int lst_status)
{
	char	*temp;
	char	*result;
	int		i;

	i = 0;
	if (!cmd_args)
		return (ft_strdup(""));
	cmd_args++;
	if (cmd_args[0] == '?')
		return (ft_itoa(lst_status));
	if (cmd_args[0] == '0')
		return (ft_strdup("MiNyanShell nyan~ :3"));
	if (ft_isdigit(cmd_args[0]))
		return (ft_strdup(""));
	temp = ft_calloc(sizeof(char), ft_strlen(cmd_args) + 1);
	if (!temp)
		return (NULL);
	while (cmd_args[i] != '\0' && (ft_isalpha(cmd_args[i])
			|| (cmd_args[i] == '_')))
	{
		temp[i] = cmd_args[i];
		i++;
	}
	result = helper(envyan, temp);
	return (free(temp), result);
}

char	*insert_expanded(char *args, int j, char *expanded)
{
	int		skip_len;
	char	*result;

	skip_len = 1;
	if (!expanded)
		return (NULL);
	result = ft_calloc(sizeof(char), (ft_strlen(args) + ft_strlen(expanded)
				+ 3));
	if (!result)
		return (NULL);
	while (args[j + skip_len] != '\0' && (ft_isalpha(args[j + skip_len])
			|| args[j + skip_len] == '_'))
		skip_len++;
	if ((skip_len == 1 && ((args[j + skip_len] == '?' || ft_isdigit(args[j
							+ skip_len])))))
		skip_len++;
	ft_memcpy(result, args, j);
	ft_memcpy(result + j, expanded, ft_strlen(expanded));
	ft_memcpy(result + j + ft_strlen(expanded), args + j + skip_len,
		ft_strlen(args) - skip_len - j);
	return (result);
}
