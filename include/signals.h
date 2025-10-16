/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:55:39 by rmedeiro          #+#    #+#             */
<<<<<<< HEAD:signals/signals.h
/*   Updated: 2025/10/15 14:52:52 by pfreire-         ###   ########.fr       */
=======
/*   Updated: 2025/10/16 15:01:45 by rmedeiro         ###   ########.fr       */
>>>>>>> ricardo:include/signals.h
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
<<<<<<< HEAD:signals/signals.h
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
=======
    
typedef struct s_UwU t_mini;
>>>>>>> ricardo:include/signals.h

typedef enum e_sigmode
{
    PROMPT = 0,
    PARENT_WAIT,
    CHILD_EXEC        
}   t_sigmode;

void set_current_mini(t_mini *mini);
t_mini *get_current_mini(void);
void sigint_prompt_handler(int sig);
void ignore_signal_handler(int sig);
void minyanshell_signals(t_sigmode mode);

#endif