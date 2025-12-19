/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:25:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/15 14:53:35 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	error_exit(const char *message)
{
	perror(message);
	exit(1);
}

void	cmd_not_found_msg(char *cmd)
{
	ft_putstr_fd("MiNyanshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

void	path_not_found_msg(char *cmd)
{
	ft_putstr_fd("MiNyanshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	warn_heredoc_eof(char *lim)
{
	write(STDERR_FILENO,
		"warning: here-document delimited by end-of-file (wanted '", 58);
	write(STDERR_FILENO, lim, ft_strlen(lim));
	write(STDERR_FILENO, "')\n", 3);
}
