/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:33:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/22 09:02:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../MiNyanShell.h"
#include "errno.h"

static int extract_exit_code(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (0);
}

void wait_for_children(t_mini *mini, pid_t last_pid)
{
    int   status;
    pid_t pid;

    status = 0;
    while (1)
    {
        pid = wait(&status);
        if (pid == -1)
        {
            if (errno == EINTR)       // interrompido por sinal?
                continue;             // tenta de novo
            else                      // ECHILD - não há mais childs para esperar
                break;
        }
        if (pid == last_pid)
            mini->last_status = extract_exit_code(status);
    }
}




