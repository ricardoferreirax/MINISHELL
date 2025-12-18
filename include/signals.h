/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:55:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 13:56:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <signal.h>

typedef struct s_UwU	t_mini;

typedef enum e_sigmode
{
	PROMPT = 0,
	PARENT_WAIT,
	CHILD_EXEC
}						t_sigmode;

void					set_current_mini(t_mini *mini);
t_mini					*get_current_mini(void);
void					sigint_prompt_handler(int sig);
void					ignore_signal_handler(int sig);
void					minyanshell_signals(t_sigmode mode);
void					sigint_heredoc(int sig);
void					setup_heredoc_signals(void);
