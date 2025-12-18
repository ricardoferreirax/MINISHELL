/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:31:07 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:07:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envyan.h"
#include "../include/execution.h"

static int	print_pwd_from_envyan(t_envyan *envyan)
{
	char	*pwd;

	pwd = envyan_get_value(envyan, "PWD");
	if (pwd)
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	ft_putstr_fd("MiNyanShell: pwd: PWD not set\n", STDERR_FILENO);
	return (1);
}

int	ft_pwd(t_cmd *cmd, t_mini *mini)
{
	char	*cwd;
	int		status;

	(void)cmd;
	if (cmd && cmd->args && cmd->args[1] && cmd->args[1][0] == '-')
	{
		ft_putstr_fd("MiNyanShell: pwd: options are not supported\n",
			STDERR_FILENO);
		mini->last_status = 1;
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		status = print_pwd_from_envyan(mini->envyan);
		mini->last_status = status;
		return (status);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	mini->last_status = 0;
	return (0);
}
