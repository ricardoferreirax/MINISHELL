/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:42:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 11:30:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "MiNyanShell.h"
# include <stdbool.h>

int parse_cmd(t_cmd *cmd, char **tokens, int *i);
char **init_mini(t_mini *nyan, char *cmdline);
void fill_mini(t_mini *nyan, char **pipes);
int redir_append_cmd(t_cmd *cmd, t_redir_type redir_type, char *arg);
bool is_redir(char *str);
char	**split_ignore_quotes(char *str, char c);
t_cmd *cmd_new(void);
int add_arg_cmd(t_cmd *cmd, const char *token);
int arr_size(void **arr);
char	*skip_whitespaces(char *str);
bool no_unclosed_quotes(char *str);
bool no_forbidden_actions(char *str);
void free_redirs(t_redir *redir);

#endif
