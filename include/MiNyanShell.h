/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiNyanShell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:19:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/18 13:56:07 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINYANSHELL_H
# define MINYANSHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_redir	t_redir;
typedef struct s_OwO	t_cmd;

typedef enum e_token_type
{
	REDIR_INVALID = -1,
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}						t_redir_type;

typedef struct s_envyan
{
	char				*key;
	char				*value;
	struct s_envyan		*next;
}						t_envyan;

typedef struct s_redir
{
	char				*file;
	char				*delimiter;
	t_redir_type		type;
	bool				expansion;
	struct s_redir		*next;
}						t_redir;

typedef struct s_OwO
{
	char				**args;
	t_redir				*redirs;
	int					in_fd;
	t_cmd				*next;
}						t_cmd;

typedef struct s_UwU
{
	t_cmd				*head;
	t_envyan			*envyan;
	int					last_status;
	int					in_pipeline;
}						t_mini;

int						print_minyanshell(void);
uint32_t				hash_file(const char *path);

#endif
