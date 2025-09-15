/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/15 16:34:15 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
#define MINYANSHELL_H

#include "libft/libft.h"

//Base Structs, hand s off dude, no touching these

typedef struct s_OwO;

typedef struct s_0w0
{
	bool hero_doc;
	bool append;
	char *delimiter;
	char **args;
	char *cmd;
	s_0w0 *next;
	s_OwO *last;
}	t_subcmd;

typedef struct s_OwO
{
	bool pipe;
	t_subcmd *head;
	s_OwO *next;
}	t_cmd;

//base structs end

typedef struct s_UwU
{
	t_cmd *head;
	t_cmd *tail;
	char **env;
	
}	t_mini;



#endif