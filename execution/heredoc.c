/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/24 22:57:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "execution.h"

int handle_heredoc(char *delimiter)
{
    int   pipefd[2];
    char *line;

    if (pipe(pipefd) == -1)
    {
        perror("minishell: heredoc pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line) // CTRL+D
        {
            write(STDOUT_FILENO, "warning: heredoc delimited by end-of-file\n", 42);
            break;
        }
        if (strcmp(line, delimiter) == 0) // encontrou o delimitador
        {
            free(line);
            break;
        }
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    return (pipefd[0]);
}

int process_all_heredocs(t_cmd *cmd_list)
{
    t_cmd     *cmd;
    t_subcmd  *sub;
    t_redir   *redir;

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
                    sub->in_fd = handle_heredoc(redir->file);
                    if (sub->in_fd == -1)
                        return (1); // erro ou CTRL+D
                }
                redir = redir->next;
            }
            sub = sub->next;
        }
        cmd = cmd->next;
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