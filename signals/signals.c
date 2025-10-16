/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:56:16 by rmedeiro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/15 14:52:32 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
=======
/*   Updated: 2025/10/16 16:39:52 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/signals.h"
>>>>>>> ricardo

t_mini *g_mini = NULL;

void set_current_mini(t_mini *mini)
{
    g_mini = mini;
}

t_mini *get_current_mini(void)
{
    return (g_mini);
}

void sigint_prompt_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        if (get_current_mini())
            get_current_mini()->last_status = 130;
    }
}

void ignore_signal_handler(int sig)
{
    (void)sig;
}

void minyanshell_signals(t_sigmode mode)
{
    if (mode == PROMPT)
    {
        signal(SIGINT,  sigint_prompt_handler);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (mode == PARENT_WAIT)
    {
        signal(SIGINT,  ignore_signal_handler);
        signal(SIGQUIT, ignore_signal_handler);
    }
    else if (mode == CHILD_EXEC)
    {
        signal(SIGINT,  SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
}
