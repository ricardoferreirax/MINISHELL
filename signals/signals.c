/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:56:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 14:52:32 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void interactive_handler(int signum)
{
    
}

static void non_interactive_handler(int signum)
{
    (void)signum; // Ignore the signal
}

void set_interactive_signals(void)
{
    signal(SIGINT,  interactive_handler);
    signal(SIGQUIT, SIG_IGN);
}

void set_non_interactive_signals(void)
{
    signal(SIGINT,  non_interactive_handler);
    signal(SIGQUIT, non_interactive_handler);
}

void set_child_signals(void)
{
    
}