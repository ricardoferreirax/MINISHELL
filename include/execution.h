/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/08 16:43:55 by pfreire-         ###   ########.fr       */
=======
/*   Updated: 2025/10/15 14:03:03 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo
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
<<<<<<< HEAD
=======
#define  EXPORT_OK 0
#define  EXPORT_ERROR 1
>>>>>>> ricardo

typedef struct s_UwU	t_mini;
typedef struct s_0w0	t_subcmd;

typedef struct s_pipeline
{
	pid_t				pid;
	int					pipefd[2];
	int					prev_pipefd;
	int					last_status;
	t_mini				*mini;
}						t_pipeline;

int						execute_pipeline(t_cmd *cmd_list, t_mini *mini);
int						process_all_heredocs(t_cmd *cmd_list, t_mini *mini);
int						apply_redirs_in_child(t_cmd *cmd);
int						execute_multiple_cmds(t_cmd *cmds, t_mini *mini);
int						execute_external_cmd(t_cmd *cmd, t_mini *mini);
int						execute_single_cmd(t_cmd *cmd, t_mini *mini);
int						execute_redirs_without_cmd(t_cmd *cmd, t_mini *mini);
<<<<<<< HEAD
void					execute_external_in_child(t_cmd *cmd,
							char **envyan_array);
=======
void execute_external_in_child(t_cmd *cmd, char **envyan_array, t_mini *mini);
>>>>>>> ricardo
char					*handle_cmd_path(char *cmd, char **envp);
void					child_execute_cmd(t_cmd *cmd, t_pipeline *pp);
int						execute_builtin(t_cmd *cmd, t_mini *mini);
bool					is_builtin(char *cmd);
int						wait_for_single(pid_t pid);
int						safe_dup2_and_close(int oldfd, int newfd);
void					reset_fds(int stdin_fd, int stdout_fd);
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
<<<<<<< HEAD
=======
int						ft_unset(t_cmd *cmd, t_mini *mini);
int						ft_export(t_cmd *cmd, t_mini *mini);
void					assign_envyan_key(t_mini *mini, char *arg);
int 					validate_export_arg(char *str);
char					**create_export_array(t_envyan *head);
void					sort_export_entries(char **env_array);
t_envyan *get_last_envyan(t_envyan *head);
void minyanshell_exit_cleanup(t_mini *mini);
void cleanup_iteration(t_mini *mini);
void free_cmd_list(t_cmd **head_ptr);
void free_envyan(t_envyan **head);
void minyanshell_child_cleanup_and_exit(t_mini *mini, int status);
>>>>>>> ricardo

int						execute_builtin(t_cmd *cmd, t_mini *mini);
bool					is_builtin(char *cmd);

<<<<<<< HEAD
int						cd_to_home(t_mini *mini);
int						cd_to_oldpwd(t_mini *mini);
int						cd_to_parent(t_mini *mini);
int						cd_error(t_mini *mini, char *msg, char *path);
int						update_pwd_after_chdir(t_mini *mini);
void					set_pwd_from_path(t_mini *mini, char *new_path);
char					*get_envyan(t_mini *mini, char *key);

=======
>>>>>>> ricardo
#endif
