/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/17 18:27:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

static char	**ft_get_envpath_dirs(char **envp)
{
	char	**path_dirs;
	char	*env_path;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	path_dirs = NULL;
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
		return(NULL);
	return (path_dirs);
}

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

char	*ft_cmd_path(char *cmd, char **envp)
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