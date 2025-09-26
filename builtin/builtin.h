/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:17:37 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/25 15:54:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_0w0
{
	t_redir_type		type;
	char				*delimiter;
	char				**args;
	char				*cmd;
	char				*infile;
	char				*outfile;
	t_subcmd			*next;
	t_redir				*redirs;
	t_cmd_mode			cmd_type;
	int					in_fd;
	int					out_fd;
}						t_subcmd;

typedef struct s_mini {
    char **env;
    int   last_status;
}   t_mini;

int ft_echo(t_subcmd *subcmd, t_mini *mini);
int ft_pwd(t_subcmd *subcmd, t_mini *mini);
int ft_env(t_subcmd *subcmd, t_mini *mini);
int ft_exit(t_subcmd *subcmd, t_mini *mini);
int ft_export(t_subcmd *subcmd, t_mini *mini);
int ft_unset(t_subcmd *subcmd, t_mini *mini);
int ft_cd(t_subcmd *subcmd, t_mini *mini);

int exec_builtin(t_subcmd *subcmd, t_mini *mini);

#endif