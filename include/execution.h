/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/07 19:37:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

#define CONTINUE -1
#define NO_CMD 0
#define ERROR 1
#define NOT_BUILTIN -1

typedef struct s_UwU   t_mini;
typedef struct s_0w0   t_subcmd;

typedef struct s_pipeline
{
    pid_t pid;
    int pipefd[2];
    int prev_pipefd;
    int last_status;
    t_mini *mini;
} t_pipeline;

typedef struct s_redir
{
    char *file;
    char *delimiter;
    t_redir_type type;
    struct s_redir *next;
}   t_redir;

int execute_pipeline(t_cmd *cmd_list, t_mini *mini);
int process_all_heredocs(t_cmd *cmd_list, t_mini *mini);
int apply_redirs_in_child(t_cmd *cmd);
int execute_multiple_cmds(t_cmd *cmds, t_mini *mini);
int execute_external_cmd(t_cmd *cmd, t_mini *mini);
int execute_single_cmd(t_cmd *cmd, t_mini *mini);
int execute_redirs_without_cmd(t_cmd *cmd, t_mini *mini);
void execute_external_in_child(t_cmd *cmd, char **envyan_array);
char	*handle_cmd_path(char *cmd, char **envp);
void child_execute_cmd(t_cmd *cmd, t_pipeline *pp);
int execute_builtin(t_cmd *cmd, t_mini *mini);
bool is_builtin(char *cmd);
int wait_for_single(pid_t pid);
int safe_dup2_and_close(int oldfd, int newfd);
void reset_fds(int stdin_fd, int stdout_fd);
void close_heredoc(t_cmd *cmd);
void close_fd_safe(int *fd);
int safe_fork(t_cmd *cmd, t_pipeline *pp);
void handle_fork_error(t_cmd *current_cmd, t_pipeline *pp);
void free_args(char **args);
void	ft_free_str(char **str);
void	error_exit(const char *message);
void	cmd_not_found_msg(char *cmd);
void	path_not_found_msg(char *cmd);
void warn_heredoc_eof(char *lim);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void free_str_array(char **arr);
void close_all_heredoc_fds(t_cmd *head);

#endif
