/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:17:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 13:47:28 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include "MiNyanShell.h"

int ft_echo(t_cmd *cmd);
int ft_pwd(t_cmd *cmd, t_mini *mini);
int ft_env(t_cmd *cmd, t_mini *mini);
int ft_cd(t_mini *mini, char **args);

int execute_builtin(t_cmd *cmd, t_mini *mini);
bool is_builtin(char *cmd);

int	cd_to_home(t_mini *mini);
int	cd_to_oldpwd(t_mini *mini);
int	cd_to_parent(t_mini *mini);
int	cd_error(t_mini *mini, char *msg, char *path);
int	update_pwd_after_chdir(t_mini *mini);
void	set_pwd_from_path(t_mini *mini, char *new_path);
char *get_envyan(t_mini *mini, char *key);

#endif