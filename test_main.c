/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 16:07:05 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	main(int argc, char **argv, char **env)
{
	char **arr;
	int i = 0;
	char *cmd;
	// printf("%s\n", argv[i]);
	cmd = readline("> ");
	while (argc)
	{
		(void) argv;
		(void) env;
		if(!no_unclosed_quotes(cmd) || strcmp(cmd, "exit") == 0)
			return(ft_printf("OwO: WhAT iS tHIs? *notices open quote*\n"), 69);
		arr = split_ignore_quotes(cmd, '|');
		i = 0;
		while (arr[i] != NULL)
		{
			printf("%s / ", arr[i]);
			i++;
		}
		t_mini nyan = parser(cmd, env);
		(void) nyan;
		cmd = readline("MiNyanShell :3> ");
	}

	return (0);
}