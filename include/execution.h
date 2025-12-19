/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 13:41:08 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "MiNyanShell.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# define CONTINUE -1
# define NO_CMD 0
# define ERROR 1
# define NOT_BUILTIN -1
# define EXPORT_OK 0
# define EXPORT_ERROR 1
# define HAS_BINARY 1
# define NOT_FOUND 0
# define EXT_ERROR -1
# define EXT_NO_PERM -2

typedef struct s_UwU	t_mini;
typedef struct s_0w0	t_subcmd;

typedef enum e_pipe_pos
{
	FIRST = 1,
	MIDDLE = 2,
	LAST = 3
}						t_pipe_pos;

typedef struct s_pipeline
{
	pid_t				pid;
	int					pipefd[2];
	int					prev_pipefd;
	int					last_status;
	t_mini				*mini;
	int					need_prev_stdin;
	int					need_next_stdout;
}						t_pipeline;

int						execute_pipeline(t_cmd *cmd_list, t_mini *mini);
int						process_all_heredocs(t_cmd *cmd_list, t_mini *mini);
int						apply_redirs_in_child(t_cmd *cmd);
int						execute_multiple_cmds(t_cmd *cmds, t_mini *mini);
int						execute_external_cmd(t_cmd *cmd, t_mini *mini);
int						execute_single_cmd(t_cmd *cmd, t_mini *mini);
int						execute_redirs_without_cmd(t_cmd *cmd, t_mini *mini);
void					execute_external_in_child(t_cmd *cmd,
							char **envyan_array, t_mini *mini);
char					*handle_cmd_path(char *cmd, char **envp, int *errcode);
void					child_execute_cmd(t_cmd *cmd, t_pipeline *pp);
int						execute_builtin(t_cmd *cmd, t_mini *mini);
bool					is_builtin(char *cmd);
int						wait_for_single(pid_t pid);
int						safe_dup2_and_close(int oldfd, int newfd);
int						reset_fds(int orig_stdin, int orig_stdout);
void					close_heredoc(t_cmd *cmd);
void					close_fd_safe(int *fd);
int						safe_fork(t_cmd *cmd, t_pipeline *pp);
void					handle_fork_error(t_cmd *current_cmd, t_pipeline *pp);
void					free_args(char **args);
void					ft_free_str(char **str);
void					error_exit(const char *message);
void					cmd_not_found_msg(char *cmd);
void					path_not_found_msg(char *cmd);
void					warn_heredoc_eof(char *lim);
void					ft_putendl_fd(char *s, int fd);
void					ft_putstr_fd(char *s, int fd);
void					free_str_array(char **arr);
void					close_all_heredoc_fds(t_cmd *head);
int						ft_echo(t_cmd *cmd);
int						ft_pwd(t_cmd *cmd, t_mini *mini);
int						ft_env(t_cmd *cmd, t_mini *mini);
int						ft_cd(t_mini *mini, char **args);
int						ft_unset(t_cmd *cmd, t_mini *mini);
int						ft_export(t_cmd *cmd, t_mini *mini);
int						ft_exit(t_cmd *cmd, t_mini *mini);
void					assign_envyan_key(t_mini *mini, char *arg);
int						validate_export_arg(char *str);
char					**create_export_array(t_envyan *head);
void					sort_export_entries(char **env_array);
t_envyan				*get_last_envyan(t_envyan *head);
void					minyanshell_exit_cleanup(t_mini *mini);
void					cleanup_iteration(t_mini *mini);
void					free_cmd_list(t_cmd **head_ptr);
void					free_envyan(t_envyan **head);
void					minyanshell_cleanup_and_exit(t_mini *mini, int status);
void					close_my_pipes(t_pipe_pos role, t_pipeline *pp);
int						is_external_resolved(t_cmd *cmd, t_mini *mini);
int						builtin_has_io(char *name);
void					prepare_first(t_cmd *cmd, t_pipeline *pp);
void					prepare_middle(t_cmd *cmd, t_pipeline *pp);
void					prepare_last(t_cmd *cmd, t_pipeline *pp);
int						expand_heredoc_line(char **line, t_redir *redir,
							t_mini *mini);
int						execute_builtin(t_cmd *cmd, t_mini *mini);
bool					is_builtin(char *cmd);

#endif
