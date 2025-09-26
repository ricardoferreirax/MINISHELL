/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 13:09:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>

#define EXEC_NORMAL 1
#define EXEC_EMPTY 0
#define EXEC_ERROR -1

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

int execute_pipeline(t_cmd *cmd, t_mini *mini);
int ft_execution(t_cmd *cmd_list, t_mini *mini);

int exec_builtin(t_subcmd *subcmd, t_mini *mini);

void	execute_subcommand(t_subcmd *subcmd, t_mini *mini);
char	*handle_cmd_path(char *cmd, char **envp);
void handle_redirs(t_subcmd *subcmd);
void wait_for_children(t_mini *mini, pid_t last_pid);


#endif