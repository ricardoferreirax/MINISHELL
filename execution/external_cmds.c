/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:25:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 13:24:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"
#include "../include/execution.h"
#include "../include/signals.h"

int	is_external_resolved(t_cmd *cmd, t_mini *mini)
{
	char	**envyan;
	char	*path;
	int		errcode;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXT_ERROR);
	envyan = envyan_to_array(mini->envyan);
	if (!envyan)
		return (EXT_ERROR);
	path = handle_cmd_path(cmd->args[0], envyan, &errcode);
	if (!path)
	{
		free_str_array(envyan);
		if (errcode == 126)
			return (EXT_NO_PERM);
		return (NOT_FOUND);
	}
	free(path);
	free_str_array(envyan);
	return (HAS_BINARY);
}

static char	*resolve_cmd_path_or_exit(t_cmd *cmd, char **envyan_array,
		t_mini *mini)
{
	char	*cmd_path;
	int		errcode;

	if (!cmd || !cmd->args || !cmd->args[0])
		minyanshell_cleanup_and_exit(mini, 0);
	cmd_path = handle_cmd_path(cmd->args[0], envyan_array, &errcode);
	if (!cmd_path)
	{
		free_str_array(envyan_array);
		if (errcode == 126)
		{
			perror(cmd->args[0]);
			minyanshell_cleanup_and_exit(mini, 126);
		}
		cmd_not_found_msg(cmd->args[0]);
		minyanshell_cleanup_and_exit(mini, 127);
	}
	return (cmd_path);
}

void	execute_external_in_child(t_cmd *cmd, char **envyan_array, t_mini *mini)
{
	char	*cmd_path;

	cmd_path = resolve_cmd_path_or_exit(cmd, envyan_array, mini);
	execve(cmd_path, cmd->args, envyan_array);
	perror(cmd_path);
	free(cmd_path);
	free_str_array(envyan_array);
	if (errno == EACCES || errno == EISDIR)
		minyanshell_cleanup_and_exit(mini, 126);
	else if (errno == ENOENT)
		minyanshell_cleanup_and_exit(mini, 127);
	minyanshell_cleanup_and_exit(mini, 1);
}

static void	setup_and_exec_child_external(t_cmd *cmd, t_mini *mini)
{
	char	**envyan;

	minyanshell_signals(CHILD_EXEC);
	if (apply_redirs_in_child(cmd) != 0)
		minyanshell_cleanup_and_exit(mini, 1);
	if (!cmd->args || !cmd->args[0])
		minyanshell_cleanup_and_exit(mini, 0);
	if (cmd->args[0][0] == '\0')
	{
		cmd_not_found_msg(cmd->args[0]);
		minyanshell_cleanup_and_exit(mini, 127);
	}
	envyan = envyan_to_array(mini->envyan);
	if (!envyan)
		minyanshell_cleanup_and_exit(mini, 1);
	execute_external_in_child(cmd, envyan, mini);
}

int	execute_external_cmd(t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	int		status;

	minyanshell_signals(PARENT_WAIT);
	pid = fork();
	if (pid == -1)
	{
		minyanshell_signals(PROMPT);
		return (perror("MiNyanShell: fork failed"), 1);
	}
	if (pid == 0)
	{
		minyanshell_signals(CHILD_EXEC);
		setup_and_exec_child_external(cmd, mini);
	}
	close_heredoc(cmd);
	status = wait_for_single(pid);
	minyanshell_signals(PROMPT);
	mini->last_status = status;
	return (status);
}
