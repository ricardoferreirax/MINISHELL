/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 10:19:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_UwU   t_mini;
typedef struct s_0w0   t_subcmd;

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

void ft_exec_cmd(t_subcmd *subcmd, char **envp);

#endif