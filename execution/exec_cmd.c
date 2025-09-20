/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/20 15:47:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static void	exec_external_cmd(t_subcmd *subcmd, t_mini *mini)
{
	char	*cmd_path;

	cmd_path = handle_command_path(subcmd->args[0], mini->env);
	if (!cmd_path)
	{
		cmd_not_found_msg(subcmd->args[0]);
		exit(127);
	}
	if (execve(cmd_path, subcmd->args, mini->env) == -1)
	{
		perror("execve failed");
		ft_free_str(subcmd->args);
		free(cmd_path);
		if (errno == EACCES)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		exit(EXIT_FAILURE);
	}
}

void	exec_subcmd(t_subcmd *subcmd, t_mini *mini)
{
	handle_redirs(subcmd);
	if (subcmd->cmd_type == CMD_BUILTIN)
	{
		exec_builtin(subcmd, mini);
		exit(0);
	}
	else if (subcmd->cmd_type == CMD_ABS_PATH
		|| subcmd->cmd_type == CMD_REL_PATH
		|| subcmd->cmd_type == CMD_SIMPLE)
		exec_external_cmd(subcmd, mini);
	else // CMD_EMPTY
		exit(0);
}
