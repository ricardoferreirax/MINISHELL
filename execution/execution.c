/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:33:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:46:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"

static int	number_of_cmds(t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	int		num_cmds;

	if (!cmd_list)
		return (0);
	current_cmd = cmd_list;
	num_cmds = 0;
	while (current_cmd)
	{
		num_cmds++;
		current_cmd = current_cmd->next;
	}
	return (num_cmds);
}

static int	execute_cmds(t_cmd *cmd_list, t_mini *mini, int num_cmds)
{
	int	status;

	if (num_cmds == 0)
		return (0);
	if (num_cmds == 1)
	{
		status = execute_single_cmd(cmd_list, mini);
		if (status == NOT_BUILTIN)
			status = execute_external_cmd(cmd_list, mini);
		return (status);
	}
	return (execute_multiple_cmds(cmd_list, mini));
}

static int	pre_execution(t_cmd *head, t_mini *mini)
{
	t_cmd	*first;

	if (!head)
		return (NO_CMD);
	if (process_all_heredocs(head, mini) != 0)
		return (ERROR);
	first = head;
	if ((!first->args || !first->args[0]) && first->redirs && !first->next)
		return (execute_redirs_without_cmd(first, mini));
	if ((!first->args || !first->args[0]) && !first->redirs)
		return (NO_CMD);
	return (CONTINUE);
}

static int	prepare_pipeline_execution(t_cmd *cmd_list, t_mini *mini)
{
	int	pre_exec;

	minyanshell_signals(PARENT_WAIT);
	pre_exec = pre_execution(cmd_list, mini);
	if (pre_exec != CONTINUE)
	{
		close_all_heredoc_fds(cmd_list);
		minyanshell_signals(PROMPT);
		mini->last_status = pre_exec;
	}
	return (pre_exec);
}

int	execute_pipeline(t_cmd *cmd_list, t_mini *mini)
{
	int	status;
	int	num_cmds;
	int	pre_exec;

	if (!mini)
		return (0);
	if (!cmd_list)
	{
		mini->last_status = 0;
		return (0);
	}
	num_cmds = number_of_cmds(cmd_list);
	mini->in_pipeline = (num_cmds > 1);
	pre_exec = prepare_pipeline_execution(cmd_list, mini);
	if (pre_exec != CONTINUE)
		return (pre_exec);
	status = execute_cmds(cmd_list, mini, num_cmds);
	close_all_heredoc_fds(cmd_list);
	minyanshell_signals(PROMPT);
	mini->last_status = status;
	return (status);
}
