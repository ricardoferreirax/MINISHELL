/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:11:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/14 12:33:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

int wait_for_single(pid_t pid)
{
   int status;

    while (1)
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            if (errno == EINTR)
                continue;     // tentou de novo se foi interrompido por sinal
            perror("MiNyanShell: waitpid");
            return (1);
        }
        break; // sai do loop se waitpid teve sucesso
    }
    if (WIFEXITED(status))   
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status)) 
        return (128 + WTERMSIG(status));
    return (1);
}

int safe_dup2_and_close(int oldfd, int newfd)
{
    if (oldfd < 0)
        return (0);
    if (oldfd == newfd)
        return (0);
    if (dup2(oldfd, newfd) == -1)
    {
        perror("minishell: dup2 error");
        close_fd_safe(&oldfd);
        return (1);
    }
    close_fd_safe(&oldfd);
    return (0);
}

void close_all_heredoc_fds(t_cmd *head)
{
    t_cmd *cur = head;
    while (cur)
    {
        if (cur->in_fd != -1) 
        { 
            close(cur->in_fd); 
            cur->in_fd = -1; 
        }
        cur = cur->next;
    }
}

void reset_fds(int stdin_fd, int stdout_fd)
{
    if (dup2(stdin_fd, STDIN_FILENO) == -1)
        perror("MiNyanshell: dup2 restore stdin");
    close_fd_safe(&stdin_fd);
    if (dup2(stdout_fd, STDOUT_FILENO) == -1)
        perror("MiNyanshell: dup2 restore stdout");
    close_fd_safe(&stdout_fd);
}

void close_heredoc(t_cmd *cmd)
{
    if (!cmd)
        return ;
    if (cmd->in_fd != -1)
    {
        close_fd_safe(&cmd->in_fd);
        cmd->in_fd = -1;
    }
}

void close_fd_safe(int *fd)
{
    if (fd && *fd >= 0)
    {
        close(*fd);
        *fd = -1;
    }
}

int safe_fork(t_cmd *cmd, t_pipeline *pp)
{
    (void)cmd;
    pp->pid = fork();
    if (pp->pid == -1)
    {
        perror("MiNyanShell: fork");
        close_fd_safe(&pp->pipefd[0]);
        close_fd_safe(&pp->pipefd[1]);
        close_fd_safe(&pp->prev_pipefd);
        return (-1);
    }
    return (0);
}

void handle_fork_error(t_cmd *current_cmd, t_pipeline *pp)
{
    (void)current_cmd;

    if (pp && pp->mini)
        pp->mini->last_status = 1;
    if (!pp)
        return ;
    close_fd_safe(&pp->prev_pipefd);
    close_fd_safe(&pp->pipefd[0]);
    close_fd_safe(&pp->pipefd[1]);
}

void free_args(char **args)
{
    int i;

    if (!args)
        return;
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

void	ft_free_str(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void free_str_array(char **arr)
{
    size_t i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}