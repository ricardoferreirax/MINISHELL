/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:37:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 13:56:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"

static int	has_numeric_chars(char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		if (ft_isdigit((unsigned char)s[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	has_only_numbers_with_sign(char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!ft_isdigit((unsigned char)s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_shlvl_from_envp(char **envp)
{
	int		i;
	char	*val;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			val = envp[i] + 6;
			if (val[0] == '\0')
				return (1);
			if (!has_numeric_chars(val))
				return (1);
			if (!has_only_numbers_with_sign(val))
				return (1);
			return (ft_atoi(val));
		}
		i++;
	}
	return (0);
}

static int	update_shlvl_if_exists(t_envyan **env_list, char *tmp)
{
	t_envyan	*cur;
	char		*new_val;

	if (!env_list || !tmp)
		return (0);
	cur = *env_list;
	while (cur)
	{
		if (cur->key && ft_strcmp(cur->key, "SHLVL") == 0)
		{
			new_val = ft_strdup(tmp);
			free(tmp);
			if (!new_val)
				return (0);
			free(cur->value);
			cur->value = new_val;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

t_envyan	*process_shlvl(t_envyan **env_list, t_envyan **current, int shlvl)
{
	t_envyan	*new_node;
	char		*shlvl_str;

	if (!env_list)
		return (NULL);
	shlvl += 1;
	if (shlvl < 0)
		shlvl = 0;
	if (shlvl > 999)
	{
		ft_putendl_fd("Minyanshell: shlvl (1000) too high, resetting to 1", 2);
		shlvl = 1;
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (*env_list);
	if (update_shlvl_if_exists(env_list, shlvl_str))
		return (*env_list);
	new_node = create_envyan_node("SHLVL", shlvl_str);
	free(shlvl_str);
	if (!new_node)
		return (*env_list);
	add_envyan_node(env_list, current, new_node);
	return (*env_list);
}
