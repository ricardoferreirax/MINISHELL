/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:17:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/30 17:21:05 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../MiNyanShell.h"
# include <stdlib.h>
# include <unistd.h>

int		ft_echo(t_subcmd *subcmd);
int		ft_pwd(t_subcmd *subcmd, t_mini *mini);

bool	is_builtin(char *cmd);
int		execute_builtin(t_subcmd *subcmd, t_mini *mini);

#endif