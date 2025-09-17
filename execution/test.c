/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:35:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/17 16:19:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_0w0
{
	t_redir_type		type;
	char				*delimiter;
	char				**args;
	char				*cmd;
	char				*infile;
	char				*outfile;
	t_subcmd			*next;
	t_cmd				*last;
	int	in_fd;
}						t_subcmd;

typedef struct s_OwO
{
	bool				pipe;
	t_subcmd			*head;
	t_cmd				*next;
	int last_status;
}						t_cmd;


// base structs end

typedef struct s_UwU
{
	t_cmd				*head;
	t_cmd				*tail;
	char				**env;
}						t_mini;

typedef struct s_exec
{
    int pipefd[2];
    pid_t pid;
    int prev_fd;
    t_mini *mini;
}
t_exec;

#endif

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
	if (access(cmd_list[0], F_OK) != 0)
		return (127);
	else if (access(cmd_list[0], X_OK) != 0)
		return (126);
	return (0); // Success
}

static char	*handle_cmd_path(char **cmd_list, char **envp)
{
	char	*cmd_path;
	int 	code;

	if (ft_strchr(cmd_list[0], '/'))
	{
		code = check_cmd_access(cmd_list[0]);
		if (code == 126)
			return (NULL);
		else if (code == 127)
			return (NULL);
		cmd_path = ft_strdup(cmd_list[0]);
	}
	else
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
	cmd_path = handle_cmd_path(sub->cmd, envp);
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

void	mini_wait(t_mini *mini, pid_t last_pid)
{
	pid_t	pid;
	int		status;

	status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)  // nenhum filho para esperar
			break ;
		if (pid == last_pid) // corresponde ao último filho ?
		{
			if (WIFEXITED(status))  // isded normally com exit
				mini->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status)) // isded por sinal
				mini->last_status = (128 + WTERMSIG(status)); // 128 + signal number
		}
	}
	if (mini->last_status == 130 || mini->last_status == 131) //
	{
		if (mini->last_status == 131)
			ft_putstr_fd("Quit (core dumped)", 2);
		ft_putstr_fd("\n", 2);
	}
}