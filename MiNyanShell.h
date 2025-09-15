/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/15 17:14:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

# include "libft/libft.h"

// Base Structs, hand s off dude, no touching these
// OK

typedef struct	s_OwO;

typedef struct s_0w0
{
	bool		hero_doc;
	bool		append;
	char		*delimiter;
	char		**args;
	char		*cmd;
	char		*infile;
	char		*outfile;
	s_0w0		*next;
	s_OwO		*last;
}				t_subcmd;

typedef struct s_OwO
{
	bool		pipe;
	t_subcmd	*head;
	s_OwO		*next;
}				t_cmd;

// base structs end

typedef struct s_UwU
{
	t_cmd		*head;
	t_cmd		*tail;
	char		**env;

}				t_mini;

#endif