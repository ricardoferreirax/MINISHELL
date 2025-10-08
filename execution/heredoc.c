/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:41:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"


// bool	is_limiter_quoted(char *s)  // delimiter tem aspas ? (TRATAR ISTO COM EXPANSÃO DE VARIÁVEIS DEPOIS))
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

static int heredoc_read_loop(t_redir *redir, t_mini *mini, int write_fd)
{
    char *line;
    (void)mini;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            warn_heredoc_eof(redir->delimiter);
            break;
        }
        if (redir->delimiter && ft_strcmp(line, redir->delimiter) == 0)
        {
            free(line);
            break;
        }
        // if (redir->expansion)
        // {
        //     expanded_line = ;
		// 	..................
        // }
        ft_putendl_fd(line, write_fd);
        free(line);
    }
    return (0);
}

static void	child_heredoc(t_redir *redir, t_mini *mini, int pipefd[2])
{
	int	exit_code;
	(void)mini;

	close_fd_safe(&pipefd[0]);               // child não lê
	signal(SIGINT, SIG_DFL);          // Ctrl+C interrompe o heredoc
	signal(SIGQUIT, SIG_IGN);
	exit_code = heredoc_read_loop(redir, mini, pipefd[1]);
	close_fd_safe(&pipefd[1]);
	exit(exit_code);
}

static int parent_heredoc_control(t_cmd *cmd, t_mini *mini, int pipefd[2], pid_t pid)
{
    int exit_code;

    close_fd_safe(&pipefd[1]);
    exit_code = wait_for_single(pid);
    if (exit_code == 130)
    {
        mini->last_status = 130;
        close_fd_safe(&pipefd[0]);
        return (1);
    }
    if (exit_code != 0)
    {
        close_fd_safe(&pipefd[0]);
        return (1);
    }
    if (cmd->in_fd != -1)     // se já havia um in_fd (ex. múltiplos heredocs), fecha o anterior
        close_fd_safe(&cmd->in_fd);
    cmd->in_fd = pipefd[0];   // guarda o read end para usar como STDIN
    return (0);
}

static int handle_single_heredoc(t_cmd *cmd, t_redir *redir, t_mini *mini)
{
    int   pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        return (perror("MiNyanShell: pipe"), 1);
    pid = fork();
    if (pid == -1)
    {
        close_fd_safe(&pipefd[0]);
        close_fd_safe(&pipefd[1]);
        return (perror("MiNyanShell: fork"), 1);
    }
    if (pid == 0)
        child_heredoc(redir, mini, pipefd);
    else
        return (parent_heredoc_control(cmd, mini, pipefd, pid));
    return (0);
}

int process_all_heredocs(t_cmd *cmd_list, t_mini *mini)
{
    t_cmd   *cmd;
    t_redir *redir;

    cmd = cmd_list;
    while (cmd)
    {
        redir = cmd->redirs;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                if (handle_single_heredoc(cmd, redir, mini) != 0)
                    return (1);
            }
            redir = redir->next;
        }
        cmd = cmd->next;
    }
    return (0);
}
