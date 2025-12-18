/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:52:20 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:06:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/envyan.h"
#include "../../include/execution.h"

static int	export_print_error(char *str)
{
	ft_putstr_fd("MiNyanShell: export: `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

int	validate_export_arg(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (export_print_error(str));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (export_print_error(str));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=')
				return (export_print_error(str));
			break ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (export_print_error(str));
		i++;
	}
	return (1);
}

void	assign_envyan_key(t_mini *mini, char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*equal = '\0';
		set_envyan_key_value(mini, arg, equal + 1);
		*equal = '=';
	}
	else
	{
		if (!envyan_key_exists(mini->envyan, arg))
			set_envyan_key_value(mini, arg, NULL);
	}
}
