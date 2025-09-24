/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/23 23:33:23 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

int	main(int argc, char **argv, char **env)
{
	char **arr;
	int i = 0;
	char *cmd;
	t_mini nyan;
	// printf("%s\n", argv[i]);
	cmd = readline("> ");
	while (argc)
	{
		(void)argv;
		(void)env;
		if (!no_unclosed_quotes(cmd) || strcmp(cmd, "exit") == 0)
			return (ft_printf("OwO: WhAT iS tHIs? *notices open quote*\n"), 69);
		i = 0;

		nyan = parser(cmd, env);
		while (nyan.head)
		{
			while(nyan.head->head)
			{
				ft_printf("%s\n", nyan.head->head->cmd);
				i = 0;
				while(nyan.head->head->args[i] != NULL)
				{
					ft_pritnf("%s\n", nyan.head->head->args[i]);
				}
			}
			i++;
		}
		cmd = readline("MiNyanShell :3> ");
	}

	return (0);
}