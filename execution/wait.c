/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:02:14 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/17 10:09:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

void	mini_wait(t_mini *mini, pid_t last_pid)
{
	pid_t	pid;
	int		status;

	status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)  // nenhum filho para esperar
			break ;
		if (pid == last_pid) // corresponde ao último filho ?
		{
			if (WIFEXITED(status))  // isded normally com exit
				mini->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status)) // isded por sinal
				mini->last_status = (128 + WTERMSIG(status)); // 128 + signal number
		}
	}
	if (mini->last_status == 130 || mini->last_status == 131) //
	{
		if (mini->last_status == 131)
			ft_putstr_fd("Quit (core dumped)", 2);
		ft_putstr_fd("\n", 2);
	}
}

// 130 = process interrupted SIGINT (Ctrl + C)
// 131 = process quit (core dumped) SIGQUIT (Ctrl + \)