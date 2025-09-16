/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/16 12:39:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

#include "parsing/parsing.h"

// Base Structs, hand s off dude, no touching these
// OK

typedef struct	s_OwO	t_cmd;
typedef struct	s_0w0	t_subcmd;

typedef struct s_0w0
{
	bool		hero_doc;
	bool		append;
	char		*delimiter;
	char		**args;
	char		*cmd;
	char		*infile;
	char		*outfile;
	t_subcmd	*next;
	t_cmd		*last;
}				t_subcmd;

typedef struct s_OwO
{
	bool		pipe;
	t_subcmd	*head;
	t_cmd		*next;
}				t_cmd;

// base structs end

typedef struct s_UwU
{
	t_cmd		*head;
	t_cmd		*tail;
	char		**env;

}				t_mini;

#endif