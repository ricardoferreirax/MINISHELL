/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:33:19 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/16 23:48:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	process_heredoc_line(t_subcmd *sub, t_mini *mini, int pipe_write_fd)
{
	char	*line;
	char	*expanded_line;

	line = readline("> ");
	if (!line) // CTRL+D
	{
        warn_heredoc_eof(sub->delimiter);
        return (1); // fim do heredoc
    }
	// se line == delimiter → fim do heredoc
	if (ft_strcmp(line, sub->delimiter) == 0)
	{
		free(line);
		return (1);
	}
	// se tiver de expandir variáveis ($VAR, $?)
	if (sub->hero_doc)
	{
		// expandir variáveis
	}
	write(pipe_write_fd, line, ft_strlen(line));
    write(pipe_write_fd, "\n", 1);
	free(line);
	return (0); // continua a ler
}


int handle_single_heredoc(t_subcmd *sub, t_mini *mini)
{
    int     pipe_fd[2];
    int     hdoc_status;
    pid_t   pid;
    
    get_pipe_and_fork(pipe_fd, &pid);
    if (pid == 0)  // CHILD
    {
        close(pipe_fd[0]); // close read end
        while (1)
        {
            if (process_heredoc_line(sub, mini, pipe_fd[1]))
                break;
        }
        close(pipe_fd[1]); // close write end
        exit(0);
    }
    else // PARENT
    {
        close(pipe_fd[1]); // close write end
        waitpid(pid, &hdoc_status, 0);
        // if (WIFSIGNALED(hdoc_status) && WTERMSIG(hdoc_status) == SIGINT)  // child killed by SIGINT
        // {
        //     sub->in_fd = -1; // abort CTRL + C  
        //     return (130);
        // }
        // sub->in_fd = pipe_fd[0]; 
    }
    return (0);
}

int prepare_heredocs_for_subcmd(t_subcmd *sub, t_mini *mini)
{
    t_subcmd *cur;
    int hdoc_status;

    hdoc_status = 0;
    cur = sub;
    while (cur)
    {
        if (cur->hero_doc)
            hdoc_status = handle_single_heredoc(cur, mini);
        cur = cur->next;
    }
    return hdoc_status; // no fim sub->in_fd aponta para o último heredoc válido
}
