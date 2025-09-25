/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/25 16:18:27 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include <unistd.h>

int	main(int argc, char **argv, char **env)
{
	int i = 0;
	char *cmd;
	t_mini nyan;
	// printf("%s\n", argv[i]);
	cmd = readline("> ");
	while (argc)
	{
		(void)argv;
		if (!no_unclosed_quotes(cmd) || strcmp(cmd, "exit") == 0)
			return (ft_printf("OwO: WhAT iS tHIs? *notices open quote*\n"), 69);

		nyan = parser(cmd, env);
		int j = 0;
		while (nyan.head)
		{
			while (nyan.head->head)
			{
				i = 0;
				ft_printf("Pipe N %d---------------------------\n", j + 1);
				ft_printf("Redirs\n");
				ft_printf("Outfile:  %s\n", nyan.head->head->outfile);
				ft_printf("Infile:  %s\n", nyan.head->head->infile);
				// ft_printf("Type:  %s\n", nyan.head->head->type);
				ft_printf("Heredoc Delim:  %s\n", nyan.head->head->delimiter);
				ft_printf("Token N %d\n", i);
				while (nyan.head->head->args[i] != NULL)
				{
					ft_printf("%s\n", nyan.head->head->args[i]);
					i++;
				}
				ft_printf("-------------------------------------\n");
				//usleep(20000);
				nyan.head->head = nyan.head->head->next;
			}
			nyan.head = nyan.head->next;
			i++;
			j++;
		}
		cmd = readline("MiNyanShell :3> ");
	}

	return (0);
}