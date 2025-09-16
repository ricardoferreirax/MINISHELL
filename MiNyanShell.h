/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/16 14:47:06 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

# include "parsing/parsing.h"
# include "stdio.h"
# include <readline/history.h>
# include <readline/readline.h>
// Base Structs, hand s off dude, no touching these
// OK

typedef struct s_OwO	t_cmd;
typedef struct s_0w0	t_subcmd;

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
	t_cmd				*tail;
	char				**env;

}						t_mini;

#endif