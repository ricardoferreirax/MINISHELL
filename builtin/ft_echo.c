/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:04:13 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/09/24 22:21:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"

typedef struct s_subcmd {
    char **args;
}   t_subcmd;


int	is_valid_n_case(char **arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i])
	{
		j = 0;
		if (arg[i][j] == '-')
		{
			j++;
			if (arg[i][j] != 'n')
				break ;
			while (arg[i][j] == 'n')
				j++;
			if (arg[i][j] != '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **arg)
{
	int	i;
	int	n_index;

	i = is_valid_n_case(arg);
	n_index = i;
	if (arg[i])
	{
		while (arg[i])
		{
			write(STDOUT_FILENO, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
		if (n_index == 1)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (n_index == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

// int main(void)
// {
//     char     *input;
//     t_subcmd sub;

//     while (1)
//     {
//         input = readline("minishell$ ");
//         if (!input) // CTRL+D
//         {
//             printf("exit\n");
//             break;
//         }
//         sub.args = ft_split_quotes(input, ' ');
//         if (sub.args && sub.args[0] && ft_strcmp(sub.args[0], "echo") == 0)
//             ft_echo(sub.args);
//         else if (sub.args && sub.args[0])
//             printf("Comando não suportado: %s\n", sub.args[0]);
//         free(input);
//         printf("--------------------------------------------------\n");
//     }
//     return (0);
// }
