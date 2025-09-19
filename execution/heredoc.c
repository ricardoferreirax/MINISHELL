/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 10:38:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static int	remove_newline_and_check(char *line, char *delimiter)
{
	size_t	len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (ft_strcmp(line, delimiter) == 0);
}

static void	read_till_delimiter(t_subcmd *sub, t_mini *mini, int pipefd[2])
{
	char	*line;
	char	*expanded;

	close(pipefd[0]); // só vamos escrever
	while (1)
	{
		line = readline("> ");
		if (!line) // Ctrl-D / EOF
		{
			warn_heredoc_eof(sub->delimiter);
			break;
		}
		if (remove_newline_and_check(line, sub->delimiter))
		{
			free(line);
			break;
		}
		if (sub->expand_hdoc_content)
		{
			// expansão de variáveis apenas se não estava entre aspas (TRATAR ISTO COM EXPANSÃO DE VARIÁVEIS DEPOIS)
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	_exit(0); // termina só o child
}

int	prepare_heredocs_for_cmd(t_cmd *cmd, t_mini *mini)
{
	t_subcmd	*node;
	int			hdoc_status = 0;

	node = cmd->head;
	while (node)
	{
		if (node->hero_doc)
		{
			// node->expand_hero_doc = !is_limiter_quoted(node->delimiter); // decide se expande ou não (DEPENDE SE O DELIMITER TEM ASPAS)
			hdoc_status = handle_heredoc(node, mini);
		}
		node = node->next;
	}
	return (hdoc_status); // no fim cmd->head->in_fd aponta para o último heredoc válido


	// precisamos de t_mini * para aceder ao env (temos de ver também depois os sinais)

int handle_heredoc(t_subcmd *subcmd, t_mini *mini)
{
    int     pipe_fd[2];
    int     hdoc_status;
    pid_t   pid;
    
    if (pipe(pipe_fd) == -1)
        error_exit("minishell: pipe failed");
    pid = fork();
    if (pid < 0)
        error_exit("minishell: fork failed");
    if (pid == 0)  // CHILD
    {
        read_till_delimiter(subcmd, mini, pipe_fd);
    }
    else // PARENT
    {
        close(pipe_fd[1]); // close write end
        waitpid(pid, &hdoc_status, 0);
        // if (WIFSIGNALED(hdoc_status) && WTERMSIG(hdoc_status) == SIGINT)  // child killed by SIGINT
        // {
        //     // ver melhor a situação do abort CTRL + C no heredoc
        // }
        // subcmd->in_fd = pipe_fd[0];  // o stdin do comando vem do heredoc através do pipe
    }
    return (0);
}

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