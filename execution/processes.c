/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/18 10:16:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static void parent_process(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (ctx->prev_fd != -1) // se existir prev_fd
        close(ctx->prev_fd); // fecha o prev_fd (read end do pipe anterior)
    if (cmd->next) // se houver próximo comando
    {
        close(ctx->pipefd[1]);
        ctx->prev_fd = ctx->pipefd[0]; // o read end do pipe é o próximo prev_fd
    }
}


static int handle_command(t_cmd *cmd, t_exec_cmd *ctx)
{
    if (cmd->next) // se houver próximo comando
    {
        if (pipe(ctx->pipefd) == -1) // cria o pipe
            error_exit("minishell: pipe failed");
    }
    ctx->pid = fork(); // cria um novo processo
    if (ctx->pid < 0)
        error_exit("minishell: fork failed");
    if (ctx->pid == 0) // CHILD
        child_process(cmd, ctx);
    else if (ctx->pid > 0) // PARENT
        parent_process(cmd, ctx);
    return (0);
}

void	mini_wait(t_cmd *mini, pid_t last_pid)
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
	// if (mini->last_status == 130 || mini->last_status == 131)
	// {
	// 	if (mini->last_status == 131)
	// 		ft_putstr_fd("Quit (core dumped)", 2);
	// 	ft_putstr_fd("\n", 2);
}


// 130 = process interrupted SIGINT (Ctrl + C)
// 131 = process quit (core dumped) SIGQUIT (Ctrl + \)

int execute_pipeline(t_cmd *cmds, t_mini *mini)
{
    t_exec_cmd ctx;

    ctx.prev_fd = -1; // inicialmente não temos prev_fd
    ctx.mini = mini; // guardamos o contexto do mini para aceder ao env 
    while (cmds) // para cada comando na lista
    {
        handle_command(cmds, &ctx); // crio o pipe, faço fork e tratamos do child e do parent
        cmds = cmds->next;
    }
    mini_wait(mini, ctx.pid); // espera pelo último filho
    return (cmds->last_status); // devolve o status do último comando
}
