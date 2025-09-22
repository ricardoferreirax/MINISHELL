/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/21 22:27:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_UwU   t_mini;
typedef struct s_0w0   t_subcmd;

typedef enum e_cmd_mode
{
	NONE_CMD,
	BUILTIN_CMD,
	ABS_PATH_CMD,
	REL_PATH_CMD,
	SIMPLE_CMD
}	t_cmd_mode;

typedef struct s_exec_cmd
{
    pid_t pid;
    int pipefd[2];
    int prev_fd;
    t_mini *mini;
} t_exec_cmd;

typedef struct s_redir
{
    char *file;
    t_redir_type type;
    struct s_redir *next;
}   t_redir;

int ft_execution(t_cmd *cmd_list, t_mini *mini);
int ft_pipeline(t_cmd *cmds, t_mini *mini);
void	exec_subcmd_with_redirs(t_subcmd *subcmd, t_mini *mini);
int exec_single_cmd(t_subcmd *subcmd, t_mini *mini);
char	*handle_cmd_path(char *cmd, char **envp);
void child_process(t_cmd *cmd, t_exec_cmd *ctx);
void handle_redirs(t_subcmd *subcmd);
void wait_for_children(t_mini *mini, pid_t last_pid);


#endif