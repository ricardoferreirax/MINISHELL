/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:23:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:41:39 by pfreire-         ###   ########.fr       */
=======
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:23:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/09 09:22:38 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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
    orig_stdin  = dup(STDIN_FILENO);
    orig_stdout = dup(STDOUT_FILENO);
    if (orig_stdin == -1 || orig_stdout == -1)
        return (perror("MiNyanShell: dup original fds"), 1);
    if (apply_redirs_in_child(cmd) != 0)
    {
        reset_fds(orig_stdin, orig_stdout);
        close_heredoc(cmd);
    	mini->last_status = 1;
        return (1);
    }
    status = execute_builtin(cmd, mini);
    reset_fds(orig_stdin, orig_stdout);
    close_heredoc(cmd);
    mini->last_status = status;
    return (0);
}
