/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envyan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:25:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 02:22:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

static void	handle_first_node_replacement(t_envyan *env_head, t_envyan *new_node)
{
	char	*temp_key;
	char	*temp_value;
	t_envyan	*temp_next;

	temp_key = env_head->key;
	temp_value = env_head->value;
	temp_next = env_head->next;
	env_head->key = new_node->key;
	env_head->value = new_node->value;
	env_head->next = new_node->next;
	new_node->key = temp_key;
	new_node->value = temp_value;
	new_node->next = temp_next;
	env_head->next = new_node;
}

static void	update_envyan_var(t_envyan *env, char *value)
{
	free(env->value);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
}

void	set_env_value(t_envyan *env_head, char *key, char *value)
{
	t_envyan	*envyan;
	t_envyan	*prev;
	t_envyan	*new_node;

	envyan = env_head;
	prev = NULL;
	if (!env_head)
		return ;
	while (envyan)
	{
		if (ft_strncmp(envyan->key, key, ft_strlen(key) + 1) == 0)
		{
			update_envyan_var(envyan, value);
			return ;
		}
		prev = envyan;
		envyan = envyan->next;
	}
	new_node = create_envyan_node(key, value);
	if (!new_node)
		return ;
	if (prev)
		prev->next = new_node;
	else
		handle_first_node_replacement(env_head, new_node);
}