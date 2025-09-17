/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:22:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/17 14:24:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"

typedef struct s_exec_cmd
{
    int pipefd[2];
    pid_t pid;
    int prev_fd;
    t_mini *mini;
}
t_exec_cmd;