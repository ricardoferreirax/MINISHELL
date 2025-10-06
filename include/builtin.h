/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:17:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 00:46:02 by rmedeiro         ###   ########.fr       */
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

int execute_builtin(t_cmd *cmd, t_mini *mini);
bool is_builtin(char *cmd);

#endif