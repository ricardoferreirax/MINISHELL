/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/28 18:52:06 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include <readline/readline.h>
#include <readline/history.h>


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

int heredoc_read_loop(t_redir *redir, t_mini *mini, int write_fd)
{
    char *line;
	(void)mini;

    while (1)
    {
        line = readline("> ");
        if (!line)  // EOF (Ctrl+D) antes do delimiter */
        {
            warn_heredoc_eof(redir->delimiter);
            break;
        }
        if (redir->delimiter != NULL && ft_strcmp(line, redir->delimiter) == 0)
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

	close(pipefd[0]);               // child não lê
	signal(SIGINT, SIG_DFL);          // Ctrl+C interrompe o heredoc
	signal(SIGQUIT, SIG_IGN);
	exit_code = heredoc_read_loop(redir, mini, pipefd[1]);
	close(pipefd[1]);
	exit(exit_code);
}

int parent_heredoc_control(t_subcmd *sub, t_mini *mini, int pipefd[2], pid_t pid)
{
    int exit_code;

    close(pipefd[1]);
    exit_code = wait_for_single(pid);
	if (exit_code == 130)
    {
        mini->last_status = 130;       /* ctrl + c durante o heredoc */
        close(pipefd[0]);
        return (1);
    }
    if (exit_code != 0)
    {
        close(pipefd[0]);
        return (1);
    }
    if (sub->in_fd != -1)   // se tinha alguma redireção de input antes, fecha
        close(sub->in_fd);
    sub->in_fd = pipefd[0];          // passa a usar este heredoc como STDIN
    return (0); // sucesso
}

int handle_single_heredoc(t_subcmd *subcmd, t_redir *redir, t_mini *mini)
{
    int   pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    	return (perror("MiNyanshell: pipe"), 1);
    pid = fork();
    if (pid == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return (perror("MiNyanshell: fork"), 1);
    }
    if (pid == 0)
        child_heredoc(redir, mini, pipefd);
    else
        return (parent_heredoc_control(subcmd, mini, pipefd, pid));
    return (0);
}

int	process_all_heredocs(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd		*cmd;
	t_subcmd	*subcmd;
	t_redir		*redir;

	cmd = cmd_list;
	while (cmd)
	{
		subcmd = cmd->head;
		while (subcmd)
		{
			redir = subcmd->redirs;
			while (redir)
			{
				if (redir->type == REDIR_HEREDOC)
				{
					if (handle_single_heredoc(subcmd, redir, mini) != 0)
						return (1); // falhou um heredoc
				}
				redir = redir->next;
			}
			subcmd = subcmd->next;
		}
		cmd = cmd->next;
	}
	return (0); // sucesso
}
