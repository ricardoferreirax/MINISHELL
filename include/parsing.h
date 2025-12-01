/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:42:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/11/28 14:31:12 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "MiNyanShell.h"
# include <stdbool.h>
#include <stddef.h>
#include <unistd.h>


int parse(t_cmd *cmd, char **tokens, int *i);
char **init_mini(t_mini *nyan, char *cmdline);
int fill_mini(t_mini *nyan, char **pipes);
int redir_append(t_cmd *cmd, t_redir_type redir_type, char *arg);
bool is_redir(char *str);
char	**split_ignore_quotes(char *str, char c, int i);
t_cmd *cmd_new(void);
int add_arg(t_cmd *cmd, const char *token);
int arr_size(void **arr);
int count_whitespaces(char *str);
bool no_unclosed_quotes(char *str);
bool no_forbidden_actions(char *str);
void free_redirs(t_redir *redir);
bool good_syntax(char *str);
int	count_words_ignore_quotes(char *str, char c);
bool	been_expanded(char *str);
void	remove_placeholder(char *s);

// expanser
int	expanser(char **final, t_envyan *env, int status);

//add spaces
char	**add_spaces(char *pipe);

//remove quotes
char	**remove_quotes(char **arr);
#endif
