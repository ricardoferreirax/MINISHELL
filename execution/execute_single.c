/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:23:04 by rmedeiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/15 14:47:31 by pfreire-         ###   ########.fr       */
=======
/*   Updated: 2025/10/16 15:25:46 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"

int execute_single_cmd(t_cmd *cmd, t_mini *mini)
{
    int orig_stdin;
    int orig_stdout;
    int status;

    if (!cmd || !cmd->args || !cmd->args[0])
	{
		close_heredoc(cmd);
		mini->last_status = 0;
		return (0);
	}
    if (!is_builtin(cmd->args[0]))
		return (NOT_BUILTIN);
	minyanshell_signals(PARENT_WAIT);
    orig_stdin  = dup(STDIN_FILENO);
    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdin == -1 || orig_stdout == -1)
    {
        minyanshell_signals(PROMPT);
        return (perror("MiNyanShell: dup original fds"), 1);
    }
    if (apply_redirs_in_child(cmd) != 0)
    {
        reset_fds(orig_stdin, orig_stdout);
        close_heredoc(cmd);
		minyanshell_signals(PROMPT);
    	mini->last_status = 1;
        return (1);
    }
    status = execute_builtin(cmd, mini);
    reset_fds(orig_stdin, orig_stdout);
    close_heredoc(cmd);
	minyanshell_signals(PROMPT);
    mini->last_status = status;
    return (0);
}
