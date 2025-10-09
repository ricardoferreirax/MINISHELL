/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:20:03 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 21:25:30 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/execution.h"
#include "../include/builtin.h"
#include "../include/envyan.h"

static int export_ident_error(const char *s)
{
    ft_putstr_fd("MiNyanShell: export: `", STDERR_FILENO);
    ft_putstr_fd((char *)s, STDERR_FILENO);
    ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
    return 0;
}

static int is_argument_valid(char *str)
{
    int i;

    if (!str || str[0] == '\0')
        return (export_ident_error(str));

    i = 0;
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (export_ident_error(str));
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
            return (export_ident_error(str));
        i++;
    }
    return (1);
}

static int process_export_arg(t_mini *mini, char *arg)
{
    if (!arg || arg[0] == '\0')
        return (0);
    if (!is_argument_valid(arg))
        return (1);
    if (!handle_append(mini, arg))
        handle_assignment(mini, arg);
    return (0);
}

static int write_export(t_cmd *cmd)
{
    int i;

    i = 1;
    while (cmd && cmd->cmd_args && cmd->cmd_args[i])
    {
        if (cmd->cmd_args[i][0] != '\0')
            return (0);
        i++;
    }
    return (1);
}

int	handle_no_args(t_mini *mini)
{
	char	**envyan_array;
	int		i;

	envyan_array = env_to_array_export(mini->envyan);
	bubble_sort(envyan_array);
	i = 0;
	while (envyan_array[i])
	{
		printf("declare -x %s\n", envyan_array[i]);
		free(envyan_array[i]);
		i++;
	}
	free(envyan_array);
	return (0);
}

int ft_export(t_cmd *cmd, t_mini *mini)
{
    int i;
	int status;
    int error_flag;

    if (!mini)
        return (1);
    if (!cmd || !cmd->cmd_args || !cmd->cmd_args[1] || write_export(cmd))
        return (handle_no_args(mini));
    error_flag = 0;
    i = 1;
    while (cmd->cmd_args[i])
	{
    	status = process_export_arg(mini, cmd->cmd_args[i]);
    	if (status != 0)
        	error_flag = 1;
    	i++;
	}
    mini->last_status = (error_flag != 0);
    return (error_flag);
}
