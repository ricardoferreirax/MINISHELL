/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:21:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:45:29 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/envyan.h"

void	set_pwd_from_path(t_mini *mini, char *new_path)
{
	char	*prev_path;   // OLDPWD

	if (!mini || !new_path)
		return ;
	prev_path = get_envyan(mini, "PWD");
	if (prev_path)
	{
		set_envyan_key_value(mini, "OLDPWD", prev_path);
		free(prev_path);
	}
	set_envyan_key_value(mini, "PWD", new_path);
}

static int apply_cd_path(t_mini *mini, char *target_path)
{
    if (!target_path || target_path[0] == '\0')
        return (cd_to_home(mini));
    if (chdir(target_path) != 0)
    {
        perror("Minyanshell: Error changing directory!");
        mini->last_status = 1;
        return (1);
    }
    return (update_pwd_after_chdir(mini));
}

static int	update_pwd_from_cwd(t_mini *mini, char *current_path)
{
	if (!mini)
		return (1);
	if (!current_path)
		return (cd_error(mini, "Minyanshell: getcwd failed", NULL));
	set_pwd_from_path(mini, current_path);
	free(current_path);
	mini->last_status = 0;
	return (0);
}

int ft_cd(t_mini *mini, char **args)
{
    char *target_path;
    char *current_path;

    if (!mini || !args)
    {
        mini->last_status = 1;
        return (1);
    }
    target_path = NULL;
    if (args[1])
        target_path = args[1];
    if (!target_path || target_path[0] == '\0' || strcmp(target_path, "~") == 0)
        return (cd_to_home(mini));
    if (strcmp(target_path, "-") == 0)
        return (cd_to_oldpwd(mini));
    if (strcmp(target_path, "..") == 0)
        return (cd_to_parent(mini));
    if (strcmp(target_path, ".") == 0 || strcmp(target_path, "./") == 0)
    {
        current_path = getcwd(NULL, 0);
        return (update_pwd_from_cwd(mini, current_path));
    }
    return (apply_cd_path(mini, target_path));
}
