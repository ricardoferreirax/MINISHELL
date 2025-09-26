/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/26 13:03:54 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"

void	print_type(t_redir_type type)
{
	if (type == REDIR_IN)
		printf("REDIR IN\n");
	if (type == REDIR_OUT)
		printf("REDIR OUT\n");
	if (type == REDIR_APPEND)
		printf("REDIR APPEND\n");
	if (type == REDIR_HEREDOC)
		printf("REDIR HEREDOC\n");
	if (type == REDIR_INVALID)
		printf("REDIR INVALID\n");
}

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
			ft_printf("Pipe N %d---------------------------\n", j + 1);
			int k = 0;
			while (nyan.head->head)
			{
				ft_printf("Sub CMD N %d---------------\n", k);
				i = 0;
				print_type(nyan.head->head->type);
				ft_printf("Outfile:  %s\n", nyan.head->head->outfile);
				ft_printf("Infile:  %s\n", nyan.head->head->infile);
				// ft_printf("Type:  %s\n", nyan.head->head->type);
				ft_printf("Heredoc Delim:  %s\n", nyan.head->head->delimiter);
				ft_printf("CMD:  %s\n", nyan.head->head->cmd);
				ft_printf("Token N %d\n", i);
				ft_printf("Args->\n", i);
				while (nyan.head->head->args
					&& nyan.head->head->args[i] != NULL)
				{
					ft_printf("\t%s\n", nyan.head->head->args[i]);
					i++;
				}
				ft_printf("-------------------------------------\n");
				nyan.head->head = nyan.head->head->next;
				k++;
			}
			nyan.head = nyan.head->next;
			i++;
			j++;
		}
		cmd = readline("MiNyanShell :3> ");
	}

	return (0);
}