/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:54:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/29 17:05:39 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

static void	setup_child_pipes(t_cmd *cmd, t_pipeline *pp)
{
	if (pp->prev_pipefd != -1)
	{
		if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
			exit(1);
		pp->prev_pipefd = -1;
	}
	if (cmd->next)
	{
		if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
			exit(1);
		close(pp->pipefd[0]);
	}
}

void	child_execute_cmd(t_cmd *cmd, t_pipeline *pp)
{
	t_subcmd	*subcmd;

	// set_child_signals();               /* SIGINT/SIGQUIT default no filho */
	setup_child_pipes(cmd, pp);
	subcmd = cmd->head;
	if (apply_redirs_in_child(subcmd) != 0)
		exit(1);
	if (!subcmd->args || !subcmd->args[0])
		exit(0);
	if (subcmd->args[0][0] == '\0') // string vazia (“command not found”)
	{
		cmd_not_found_msg(subcmd->args[0]);
		exit(127);
	}
	if (is_builtin(subcmd->args[0]))
		// Na pipeline,os builtins executam no child
	{
		execute_builtin(subcmd, pp->mini);
		exit(pp->mini->last_status);
	}
	execute_external_cmd(subcmd, pp->mini);
}

// static void first_child(t_cmd *cmd, t_pipeline *pp)
// {
//     t_subcmd *subcmd;

//     subcmd = cmd->head;
//     if (cmd->next)
//     {
//         if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
//             error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
//         close(pp->pipefd[0]);
//     }
//     execute_subcommand(subcmd, pp->mini);
// }

// static void middle_child(t_cmd *cmd, t_pipeline *pp)
// {
//     t_subcmd *subcmd;

//     subcmd = cmd->head;
//     if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
//         error_exit("MiNyanShell :3 : dup2 failed (pipe read)");
//     if (safe_dup2_and_close(pp->pipefd[1], STDOUT_FILENO) != 0)
//         error_exit("MiNyanShell :3 : dup2 failed (pipe write)");
//     close(pp->pipefd[0]);
//     execute_subcommand(subcmd, pp->mini);
// }

// static void last_child(t_cmd *cmd, t_pipeline *pp)
// {
//     t_subcmd *subcmd;

//     subcmd = cmd->head;
//     if (safe_dup2_and_close(pp->prev_pipefd, STDIN_FILENO) != 0)
//         error_exit("MiNyanShell :3 : dup2 failed (pipe read)");

//     execute_subcommand(subcmd, pp->mini);
// }

// void child_process(t_cmd *cmd, t_pipeline *pp)
// {
//     if (pp->prev_pipefd == -1 && cmd == pp->mini->head)
//         first_child(cmd, pp);
//     else if (cmd->next)
//         middle_child(cmd, pp);
//     else if (!cmd->next)
//         last_child(cmd, pp);
// }