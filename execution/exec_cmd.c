/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:15:01 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/18 18:33:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static char	**ft_parse_cmd(char *cmd)
{
	char	**cmd_list;

	cmd_list = ft_split_quotes(cmd, ' ');
	if (!cmd_list || !cmd_list[0])
	{
		ft_free_str(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}

static int	check_cmd_access(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (127);
	else if (access(cmd, X_OK) != 0)
		return (126);
	return (0); // SUCCESS
}

static char	*handle_cmd_path(char **cmd_list, char **envp)
{
	char	*cmd_path;
	int 	code;

	if (ft_strchr(cmd_list[0], '/'))  // ABSOLUTE OR RELATIVE PATH
	{
		code = check_cmd_access(cmd_list[0]);
		if (code == 126)
			return (NULL);
		else if (code == 127)
			return (NULL);
		cmd_path = ft_strdup(cmd_list[0]);
	}
	else // SEARCH IN PATH
	{
		cmd_path = ft_cmd_path(cmd_list[0], envp);
		if (!cmd_path)
			return (NULL);
	}
	return (cmd_path);
}

void	ft_exec_cmd(t_subcmd *sub, char **envp)
{
	char	*cmd_path;

	sub->args = ft_parse_cmd(sub->cmd);
	if (!sub->args)
	{
		cmd_not_found_msg(sub->cmd);
		exit(127); // só no child
	}
	cmd_path = handle_cmd_path(sub->args, envp);
	if (!cmd_path)
	{
		cmd_not_found_msg(sub->cmd);
		ft_free_str(sub->args);
		exit(127); // só no child
	}
	if (execve(cmd_path, sub->args, envp) == -1)
	{
		perror("execve failed");
		ft_free_str(sub->args);
		free(cmd_path);
		if (errno == EACCES)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		exit(EXIT_FAILURE);
	}
}

