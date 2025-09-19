/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/19 19:51:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

# include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

# include <readline/history.h>
# include <readline/readline.h>
# include "execution/execution.h"

// Base Structs, hand s off dude, no touching these
// OK

typedef struct	s_OwO	t_cmd;
typedef struct	s_0w0	t_subcmd;

typedef enum e_token_type
{
	REDIR_INVALID = -1, // Not a redirection token
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}						t_redir_type;

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
	t_redir				*redirs;
	t_cmd_mode			cmd_type;
	int					in_fd;
	int					out_fd;
}						t_subcmd;

typedef struct s_OwO
{
	bool				pipe;
	t_subcmd			*head;
	t_cmd				*next;
}						t_cmd;

// base structs end

typedef struct s_UwU
{
	t_cmd				*head;
	char				**env;
	int 				last_status;
}						t_mini;

#endif
