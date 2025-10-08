/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:42:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 17:09:42 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "MiNyanShell.h"
# include <stdbool.h>

int		parse(t_cmd *cmd, char **tokens, int *i);
char	**init_mini(t_mini *nyan, char *cmdline);
void	fill_mini(t_mini *nyan, char **pipes);
int		redir_append(t_cmd *cmd, t_redir_type redir_type, char *arg);
bool	is_redir(char *str);
char	**split_ignore_quotes(char *str, char c);
t_cmd	*cmd_new(void);
int		add_arg(t_cmd *cmd, const char *token);
void	free_redir_list(t_redir *r);
void	fill_cmd(t_cmd *node, char **tokens);
int		arr_size(void **arr);
char	*skip_whitespaces(char *str);
bool	no_unclosed_quotes(char *str);
bool	forbidden_actions(char *str);
void	free_cmd_list(t_cmd *head);

#endif
