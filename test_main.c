/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:13:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/16 17:33:39 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiNyanShell.h"
#include "parsing/parsing.h"

int	main(int argc, char **argv, char **env)
{
	char **arr;
	int i = 0;
	char *cmd;
	// printf("%s\n", argv[i]);
	while (1)
	{
		cmd = readline("> ");
		if(!no_unclosed_quotes(cmd))
			return(ft_printf("OwO: WhAT iS tHIs? AN oPEn QuOte?\n"), 69);
		arr = split_ignore_quotes(cmd, ' ');
		while (arr[i] != NULL)
		{
			printf("%s / ", arr[i]);
			i++;
		}
	}

	return (0);
}