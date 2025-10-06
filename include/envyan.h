/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:07:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 02:25:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVYAN_H
# define ENVYAN_H

# include "MiNyanShell.h"

typedef struct s_envyan
{
	char			*key;
	char			*value;
	struct s_envyan	*next;
}	t_envyan;

t_envyan	*init_envyan(char **envp);
void	process_envyan_entry(char *entry, t_envyan **env_list, t_envyan **current);
void	add_envyan_node(t_envyan **env_list, t_envyan **current, t_envyan *new_node);
t_envyan	*create_envyan_node(char *key, char *value);
int	get_shlvl_from_envp(char **envp);
t_envyan	*process_shlvl(t_envyan **env_list, t_envyan **current, int shlvl);
void	set_env_value(t_envyan *env_head, char *key, char *value);
char	*envyan_get_value(t_envyan *head, char *key);
char	**envyan_to_array(t_envyan *envyan);
void	cleanup_env_array(char **env_array, int index);

char	*ft_itoa(int n);
int	ft_atoi(const char *str);

#endif