/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/19 22:14:00 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static char	*ft_join_dir_cmd(char *path_dir, char *cmd)
{
	char	*dir_slash;
	char	*fullpath;

	if (!path_dir || !cmd)
		return (NULL);
	dir_slash = ft_strjoin(path_dir, "/");
	if (!dir_slash)
		return (NULL);
	fullpath = ft_strjoin(dir_slash, cmd);
	free(dir_slash);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}

static char	**ft_get_envpath_dirs(char **envp)
{
	char	**path_dirs;
	char	*env_path;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!env_path)
		return (NULL);
	path_dirs = ft_split(env_path, ':');
	if (!path_dirs)
		return (NULL);
	return (path_dirs);
}

static char	*ft_cmd_path(char *cmd, char **envp)
{
	char	**path_dirs;
	char	*fullpath;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	path_dirs = ft_get_envpath_dirs(envp);
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		fullpath = ft_join_dir_cmd(path_dirs[i], cmd);
		if (fullpath && access(fullpath, F_OK | X_OK) == 0)
			return (ft_free_str(path_dirs), fullpath);
		free(fullpath);
		i++;
	}
	ft_free_str(path_dirs);
	return (NULL);
}

static int	check_cmd_access(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (127);
	else if (access(cmd, X_OK) != 0)
		return (126);
	return (0); // success
}

char	*handle_cmd_path(char *cmd, char **envp)
{
	char	*cmd_path;
	int		code;

	if (ft_strchr(cmd, '/'))
	{
		code = check_cmd_access(cmd);
		if (code != 0)
			return (NULL);
		cmd_path = ft_strdup(cmd);
	}
	else // procurar no PATH
	{
		cmd_path = ft_cmd_path(cmd, envp);
		if (!cmd_path)
			return (NULL);
	}
	return (cmd_path);
}
