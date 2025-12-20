/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:18:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/12/19 17:48:59 by rmedeiro         ###   ########.fr       */
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

static void	unsupported_ops(void)
{
	ft_dprintf(2, "MiNyanShell: unsupported operator (&&, ||, *)\n");
}

static int	process_line(t_mini *mini, char *input)
{
	char	**pipes;
	int		status;

	if (!input || !mini)
		return (-1);
	if (*input)
		add_history(input);
	if (!no_unclosed_quotes(input))
		return (ft_dprintf(2, "MiNyanShell: syntax error: unclosed quotes\n"),
			-1);
	if (!no_forbidden_actions(input))
		return (unsupported_ops(), -1);
	if (!good_syntax(input))
		return (ft_dprintf(2, "invalid Syntax nyan~\n"), -1);
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
			printf("exit\n");
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

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	if (ac != 1)
	{
		ft_dprintf(2, "MiNyanShell: %s: Invalid argument\n", av[1]);
		ft_dprintf(2, "What do you expect me to do? ╮(╯_╰)╭o");
		return (-1);
	}
	if (hash_file("MiNyanShell.txt") != 4096230629 || print_minyanshell())
		return (ft_printf("Missing critical file, refusing to continue\n"), -1);
	init_shell(&mini, envp);
	command_loop(&mini);
	minyanshell_exit_cleanup(&mini);
	return (mini.last_status);
}
