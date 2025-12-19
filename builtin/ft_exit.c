/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:48:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:07:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"

int	is_arg_valid(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("MiNyanShell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (2);
		}
		i++;
	}
	return (0);
}

static int	exit_handle_args(t_cmd *cmd, t_mini *mini, int piped,
		int *exit_code)
{
	int	arg_check;

	*exit_code = 0;
	if (!cmd->args[1])
		return (0);
	arg_check = is_arg_valid(cmd->args[1]);
	if (arg_check == 2)
	{
		*exit_code = 2;
		return (0);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("MiNyanShell: exit: too many arguments", 2);
		if (piped)
			minyanshell_cleanup_and_exit(mini, 1);
		mini->last_status = 1;
		return (1);
	}
	*exit_code = ft_atoi(cmd->args[1]);
	return (0);
}

static void	perform_exit(t_mini *mini, int piped, int exit_code)
{
	if (piped)
		minyanshell_cleanup_and_exit(mini, exit_code);
	minyanshell_exit_cleanup(mini);
	exit(exit_code);
}

int	ft_exit(t_cmd *cmd, t_mini *mini)
{
	int	exit_code;
	int	piped;
	int	status;

	if (!cmd || !cmd->args)
		return (1);
	piped = mini->in_pipeline;
	if (!piped)
		ft_putendl_fd("exit", STDOUT_FILENO);
	status = exit_handle_args(cmd, mini, piped, &exit_code);
	if (status != 0)
		return (1);
	perform_exit(mini, piped, exit_code);
	return (0);
}
