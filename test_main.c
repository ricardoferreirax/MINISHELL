/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/17 14:48:58 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	main(int argc, char **argv, char **env)
{
	char **arr;
	int i = 0;
	char *cmd;
	// printf("%s\n", argv[i]);
	while (argc)
	{
		(void) argv;
		(void) env;
		cmd = readline("> ");
		if(!no_unclosed_quotes(cmd))
			return(ft_printf("OwO: WhAT iS tHIs? *notices open quote*\n"), 69);
		arr = split_ignore_quotes(cmd, ' ');
		while (arr[i] != NULL)
		{
			printf("%s / ", arr[i]);
			i++;
		}
	}

	return (0);
}