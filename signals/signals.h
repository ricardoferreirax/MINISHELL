/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:55:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/27 14:56:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mini t_mini;

void set_interactive_signals(void);
void set_non_interactive_signals(void);
void set_child_signals(void);

#endif