/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:11:42 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/16 15:13:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>

void	get_pipe_and_fork(int pipefd[2], pid_t *pid)
{
	if (pipe(pipefd) == -1)
		error_exit("Error creating pipe.");
	*pid = fork();
	if (*pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		error_exit("Fork Failed!");
	}
}

void safe_dup2(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1)
    {
        close(oldfd);
        error_exit("Error. Dup2 failed.");
    }
}