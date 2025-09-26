/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:57:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/26 17:22:40 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "execution.h"

static int extract_exit_code(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (0);
}

static void wait_for_children(t_mini *mini, pid_t last_pid)
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

void parent_pipe_control(t_cmd *cmd, t_pipeline *pp)
{
    if (pp->prev_pipefd != -1) // Fecha o read end do pipe anterior caso ainda esteja aberto
    {
        close(pp->prev_pipefd);
        pp->prev_pipefd = -1;
    }
    if (cmd->next)  // Se houver próximo comando, mantemos o lado de leitura do pipe atual
    {
        close(pp->pipefd[1]);
        pp->prev_pipefd = pp->pipefd[0]; // o próximo comando vai ler do read end do pipe atual
    }
    else // último comando → não precisa de guardar o prev_pipefd
        pp->prev_pipefd = -1;
    if (cmd->head && cmd->head->in_fd != -1)  // Fecha o fd do heredoc se existir
    {
        close(cmd->head->in_fd);
        cmd->head->in_fd = -1;
    }
}

static int handle_pipeline_cmd(t_cmd *curr, t_pipeline *pp)
{
    if (curr->next && pipe(pp->pipefd) == -1) // cria o pipe só se houver próximo comando
    {
        perror("MiNyanshell: pipe failed");
        if (pp->prev_pipefd != -1)
        {
            close(pp->prev_pipefd);
            pp->prev_pipefd = -1;
        }
        return (1);
    }
    pp->pid = fork();
    if (pp->pid == -1)
    {
        perror("MiNyanshell: fork failed");
        return (1);
    }
    if (pp->pid == 0)
        child_process(curr, pp);  
    else
        parent_pipe_control(curr, pp, pp->pipefd);
    return (0);
}

int execute_pipeline(t_cmd *cmd_list, t_mini *mini)
{
    t_pipeline pp;
    t_cmd      *current_cmd;

    pp.pid = -1;
    pp.prev_pipefd = -1;
    pp.last_status = 0;
    pp.mini = mini;
    // set_signals();
    current_cmd = cmd_list;
    while (current_cmd)
    {
        if (handle_pipeline_cmd(current_cmd, &pp))
            return (1);
        current_cmd = current_cmd->next;
    }
    wait_for_children(pp.mini, pp.pid);
    // set_signals();
    return (pp.last_status);
}
