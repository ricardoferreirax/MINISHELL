/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:18:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/18 12:36:33 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/MiNyanShell.h"
#include "include/envyan.h"
#include "include/execution.h"
#include "include/parsing.h"
#include "include/signals.h"
#include "print/dprintf/ft_dprintf.h"
#include "print/printf/ft_printf.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	process_line(t_mini *mini, char *input)
{
	char	**pipes;
	int		status;

	status = 0;
	if (!input || !mini)
		return (-1);
	if (*input)
		add_history(input);
	if (!no_unclosed_quotes(input))
		return (ft_dprintf(2, "MiNyanShell: swyntax wewor: unclosed quotes \n")
			- 1);
	if (!no_forbidden_actions(input))
		return (ft_dprintf(2, "MiNyanShell: unsuwuppowted opewator (&&, ||,
				*)\n"), -1);
	if (!good_syntax(input))
		return (ft_dprintf(2, "inwalid Swyntax nyan~\n"), -1);
	pipes = init_mini(mini, input);
	if (!pipes)
		return (perror("init_mini"), -1);
	status = fill_mini(mini, pipes);
	free_2d((void **)pipes);
	if (!status)
		status = execute_pipeline(mini->head, mini);
	mini->last_status = status;
	return (0);
}

static void	command_loop(t_mini *mini)
{
	char	*input;

	while (1)
	{
		input = readline("MiNyanShell nyan~ :3 > ");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			printf("\nexit\n");
			break ;
		}
		if (input[0] != '\0')
			process_line(mini, input);
		free(input);
		cleanup_iteration(mini);
	}
}

static void	init_shell(t_mini *mini, char **envp)
{
	t_envyan	*last_node;
	int			shlvl;

	if (!mini)
		return ;
	mini->head = NULL;
	mini->envyan = init_envyan(envp);
	last_node = get_last_envyan(mini->envyan);
	shlvl = get_shlvl_from_envp(envp);
	mini->envyan = process_shlvl(&mini->envyan, &last_node, shlvl);
	mini->last_status = 0;
	set_current_mini(mini);
	minyanshell_signals(PROMPT);
}

void	print_env(t_envyan *env)
{
	while (env)
	{
		ft_printf("Key: %s\n", env->key);
		ft_printf("Value : %s\n", env->value);
		env = env->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	if (ac != 1)
	{
		ft_dprintf(2, "MiNyanShell: %s: Invalid argument\n", av[1]);
		ft_dprintf(2, "What do you expect me to do? ╮(╯_╰)╭o");
		return (-1);
	}
	if (print_MiNyanShell())
	{
		ft_dprintf(2, "Miwing critical MiNyanShell.txt file ");
		ft_dprintf(2, "(╥﹏╥)");
		return (ft_dprintf(2, " wefusing to continue\n"), -1);
	}
	init_shell(&mini, envp);
	command_loop(&mini);
	minyanshell_exit_cleanup(&mini);
	return (mini.last_status);
}
