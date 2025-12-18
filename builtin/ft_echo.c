/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:04:13 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:07:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int	is_valid_n_case(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args && args[i])
	{
		j = 0;
		if (args[i][j] == '-')
		{
			j++;
			if (args[i][j] != 'n')
				break ;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] != '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_index;

	if (!cmd || !cmd->args)
		return (0);
	i = is_valid_n_case(cmd->args);
	n_index = i;
	if (cmd->args[i])
	{
		while (cmd->args[i])
		{
			write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
			if (cmd->args[i + 1])
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
		if (n_index == 1)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (n_index == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
