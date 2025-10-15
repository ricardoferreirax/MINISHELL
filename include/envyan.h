/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:07:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:36:30 by pfreire-         ###   ########.fr       */
=======
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:07:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 11:54:20 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVYAN_H
# define ENVYAN_H

#include "MiNyanShell.h"

typedef struct s_UwU t_mini; 

<<<<<<< HEAD


t_envyan	*init_envyan(char **envp);
void	process_envyan_entry(char *entry, t_envyan **env_list, t_envyan **current);
void	add_envyan_node(t_envyan **env_list, t_envyan **current, t_envyan *new_node);
t_envyan	*create_envyan_node(char *key, char *value);
int	get_shlvl_from_envp(char **envp);
=======
t_envyan	*init_envyan(char **envp);
void		process_envyan_entry(char *entry, t_envyan **env_list, t_envyan **current);
void		add_envyan_node(t_envyan **env_list, t_envyan **current, t_envyan *new_node);
t_envyan	*create_envyan_node(char *key, char *value);
int			get_shlvl_from_envp(char **envp);
>>>>>>> ricardo
t_envyan	*process_shlvl(t_envyan **env_list, t_envyan **current, int shlvl);
char	*envyan_get_value(t_envyan *head, char *key);
char	**envyan_to_array(t_envyan *envyan);
void	clean_envyan_array(char **envyan_array, int index);
<<<<<<< HEAD
int set_envyan_key_value(t_mini *mini, char *key, char *value);
void	free_envyan(t_envyan *envyan);

#endif
=======
int 	set_envyan_key_value(t_mini *mini, char *key, char *value);
int envyan_key_exists(t_envyan *envyan, char *key);
void					free_envyan(t_envyan **head);

#endif
>>>>>>> ricardo
