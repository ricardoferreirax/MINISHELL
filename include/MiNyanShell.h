/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/10/16 14:45:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_redir t_redir;
typedef struct s_OwO t_cmd;

typedef enum e_token_type
{
	REDIR_INVALID = -1, // Not a redirection token
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}						t_redir_type;

typedef struct s_envyan
{
	char			*key;
	char			*value;
	struct s_envyan	*next;
}	t_envyan;

typedef struct s_redir
{
	char *file;
	char *delimiter;
	t_redir_type type;
	struct s_redir *next;
}   t_redir;

typedef struct s_OwO
{
	char						**args;
	t_redir						*redirs;
	int							in_fd;
	t_cmd						*next;
}								t_cmd;

typedef struct s_UwU
{
	t_cmd				*head;
	t_envyan			*envyan;
	int					last_status;
}						t_mini;



// typedef struct s_0w0
// {
// 	char				**args;
// 	char				*cmd;
// 	// char				*infile;
// 	// char				*outfile;
// 	int					in_fd;
// 	int					out_fd;
// 	t_redir				*redirs;
// 	t_subcmd			*next;
// }						t_subcmd;

// typedef struct s_OwO
// {
// 	t_subcmd			*head;
// 	t_cmd				*next;
// }						t_cmd;

// base structs end

t_mini					parser(char *cmd, char **env);

#endif
