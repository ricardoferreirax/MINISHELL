/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 22:16:18 by rmedeiro         ###   ########.fr       */
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
	CMD_EMPTY,
	CMD_BUILTIN,
	CMD_ABS_PATH,
	CMD_REL_PATH,
	CMD_SIMPLE
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

int	ft_execution(t_cmd *cmd_list, t_mini *mini);
int ft_pipeline(t_cmd *cmds, t_mini *mini);
void	exec_subcmd(t_subcmd *subcmd, t_mini *mini);
char	*handle_cmd_path(char *cmd, char **envp);
void child_process(t_cmd *cmd, t_exec_cmd *ctx);


#endif