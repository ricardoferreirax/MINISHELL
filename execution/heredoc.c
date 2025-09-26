/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 23:09:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

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

static int	ft_heredoc(t_redir *redir, t_mini *mini, int write_fd)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			warn_heredoc_eof(redir);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0) // encontrou o delimitador
		{
			free(line);
			break ;
		}
		// if (redir->expand)
		// {
		// 	expanded_line = expand(line, mini); ????
		// 	free(line);
		// 	line = expanded_line;
		// }
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	return (0);
}

static void	heredoc_child(t_redir *redir, t_mini *mini, int pipe_fds[2])
{
	int	exit_code;

	close(pipe_fds[0]);               // child não lê
	// signal(SIGINT, SIG_DFL);          // Ctrl+C interrompe heredoc
	// signal(SIGQUIT, SIG_IGN);
	exit_code = ft__heredoc(redir, mini, pipe_fds[1]);
	close(pipe_fds[1]);
	exit(exit_code);
}

static int	heredoc_parent(t_subcmd *sub, t_mini *mini, int pipe_fds[2], pid_t pid)
{
	int	status;

	close(pipe_fds[1]);               // parent não escreve
	waitpid(pid, &status, 0);
	/* if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		mini->last_status = 130;      // interrupção com Ctrl+C
		close(pipe_fds[0]);
		return (1);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_fds[0]);
		return (1);
	} */
	if (sub->in_fd != -1)             // já havia heredoc → fecha
		close(sub->in_fd);
	sub->in_fd = pipe_fds[0];         // usar o novo heredoc
	return (0);
}

int	handle_single_heredoc(t_subcmd *sub, t_redir *redir, t_mini *mini)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		return (perror("MiNyanshell: pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (perror("MiNyanshell: fork"), 1);
	}
	if (pid == 0)
		heredoc_child(redir, mini, pipe_fds);
	else
		return (heredoc_parent(sub, mini, pipe_fds, pid));
	return (0);
}

int	process_all_heredocs(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd		*cmd;
	t_subcmd	*sub;
	t_redir		*redir;

	cmd = cmd_list;
	while (cmd)
	{
		sub = cmd->head;
		while (sub)
		{
			redir = sub->redirs;
			while (redir)
			{
				if (redir->type == REDIR_HEREDOC)
				{
					if (handle_single_heredoc(sub, redir, mini) != 0)
						return (1); // falhou um heredoc
				}
				redir = redir->next;
			}
			sub = sub->next;
		}
		cmd = cmd->next;
	}
	return (0); // sucesso
}
