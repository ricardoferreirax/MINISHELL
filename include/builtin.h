/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:17:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/28 19:08:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include "MiNyanShell.h"

int ft_echo(t_subcmd *subcmd);
int ft_pwd(t_subcmd *subcmd, t_mini *mini);

bool is_builtin(char *cmd);
int execute_builtin(t_subcmd *subcmd, t_mini *mini);

#endif