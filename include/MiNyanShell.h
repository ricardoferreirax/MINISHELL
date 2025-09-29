/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:MiNyanShell.h
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/26 18:41:54 by pfreire-         ###   ########.fr       */
=======
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/28 22:51:33 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo:include/MiNyanShell.h
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

<<<<<<< HEAD:MiNyanShell.h
# include "libft/libft.h"
# include "parsing/parsing.h"
=======
# include "../libft/libft.h"
/* # include "parsing/parsing.h"
>>>>>>> ricardo:include/MiNyanShell.h
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct	s_OwO	t_cmd;
typedef struct	s_0w0	t_subcmd;
typedef struct s_redir t_redir;

typedef enum e_cmd_mode
{
	NONE_CMD,
	BUILTIN_CMD,
	ABS_PATH_CMD,
	REL_PATH_CMD,
	SIMPLE_CMD
}	t_cmd_mode;

typedef enum e_token_type
{
	REDIR_INVALID = -1, // Not a redirection token
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_INOUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}						t_redir_type;

typedef struct s_0w0
{
	char				**args;
	char				*cmd;
	// char				*infile;
	// char				*outfile;
	int					in_fd;
	int					out_fd;
	t_redir				*redirs;
	t_subcmd			*next;
}						t_subcmd;

typedef struct s_OwO
{
	t_subcmd			*head;
	t_cmd				*next;
}						t_cmd;

// base structs end

typedef struct s_UwU
{
	t_cmd				*head;
	char				**env;
	int					last_status;
}						t_mini;

t_mini					parser(char *cmd, char **env);

#endif
