/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:57:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/23 22:25:51 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

static int setup_pipe(int curr_pipe[2], t_pipeline *pp, t_cmd *curr_cmd)
{
    if (curr_cmd->next) // só se houver um próximo comando
    {
        if (pipe(curr_pipe) == -1) // é que tentamos criar um novo pipe
        {
            perror("MiNyanShell :3 : pipe failed");
            if (pp->prev_pipefd != -1) // em caso de erro, verifica se ainda há um prev_pipefd aberto
            {
                close(pp->prev_pipefd);
                pp->prev_pipefd = -1;
            }
            return (0); // retorna 0 para indicar ERROOOO
        }
    }
    return (1); // se o pipe foi criado com sucesso ou se não havia próximo comando
}

static void parent_pipe_control(t_cmd *cmd, t_pipeline *pp, int curr_pipe[2])
{
    if (pp->prev_pipefd != -1)
    {
        close(pp->prev_pipefd); // fecha o prev_pipefd (read end do pipe anterior)
        pp->prev_pipefd = -1;
    }
    if (cmd->next)
    {
        close(curr_pipe[1]); // o parent não escreve no pipe → fecha o write end
        pp->prev_pipefd = curr_pipe[0]; // o próximo comando vai ler do read end do pipe atual
    }
    else //se for o último comando
        pp->prev_pipefd = -1; // no precisa d guardar nada, pois não há póximo comando que use esse prev_pipefd
}

static int fork_child(t_cmd *curr_cmd, t_pipeline *pp, int curr_pipe[2])
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("MiNyanShell :3 : fork failed");
        return (-1);
    }
    if (pid == 0)
        child_process(curr_cmd, pp);
    return (pid); // o parent devolve o pid do child
}

int execute_pipeline(t_cmd *cmd, t_mini *mini)
{
    t_pipeline      pp;
    t_cmd      *curr_cmd;
    int         curr_pipe[2];

    pp.prev_pipefd = -1;
    pp.last_status = 0;
    pp.mini = mini;
    curr_cmd = cmd;
    while (curr_cmd)
    {
        if (!setup_pipe(curr_pipe, &pp, curr_cmd))
            return (1);
        if (fork_child(curr_cmd, &pp, curr_pipe) == -1)
            return (1);
        parent_pipe_control(curr_cmd, &pp, curr_pipe);
        curr_cmd = curr_cmd->next;
    }
    wait_for_children(pp.mini, pp.pid);
    return (pp.last_status);
}
