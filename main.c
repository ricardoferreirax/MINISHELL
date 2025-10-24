/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:18:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 17:20:14 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/MiNyanShell.h"
#include "include/envyan.h"
#include "include/execution.h"
#include "include/parsing.h"
#include <stdio.h>

static void	process_line(t_mini *mini, char *input)
{
	int i;
	char	**pipes;

	if (!input || !mini)
		return ;
	if (*input)
		add_history(input);
	if (!no_unclosed_quotes(input))
	{
		ft_dprintf(2, "MiNyanShell: syntax error: unclosed quotes\n");
		return ;
	}
	if (forbidden_actions(input))
	{
		ft_dprintf(2, "MiNyanShell: unsupported operator (&&, ||, *)\n");
		return ;
	}
	pipes = init_mini(mini, input);
	if (!pipes)
	{
		perror("init_mini");
		return ;
	}
	fill_mini(mini, pipes);
	free_2d((void **)pipes);
	while (mini->head)
	{
		i = 0;
		printf("Args: \n");
		while (mini->head->args[i] != NULL)
		{
			printf("%s ", mini->head->args[i]);
			i++;
		}
		printf("\n");
		mini->head = mini->head->next;
	}
	free_cmd_list(mini->head);
	mini->head = NULL;
}

static void	command_loop(t_mini *mini)
{
	char	*input;

	while (1)
	{
		input = readline("MiNyanShell> ");
		if (!input)
		{
			printf("\nexit\n");
			break ;
		}
		if (input[0] != '\0')
			process_line(mini, input);
		free(input);
	}
}

static void	init_shell(t_mini *mini, char **envp)
{
	if (!mini)
		return ;
	mini->head = NULL;
	mini->envyan = init_envyan(envp);
	mini->last_status = 0;
	// set_interactive_signals();
}

void print_env(t_envyan *env)
{
	while(env)
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
		if (av && av[1])
			ft_dprintf(2, "MiNyanShell: %s: Invalid argument\n", av[1]);
		else
			ft_dprintf(2, "MiNyanShell: Invalid argument\n");
		return (1);
	}
	init_shell(&mini, envp);
	print_env(mini.envyan);
	command_loop(&mini);
	rl_clear_history();
	free_envyan(mini.envyan);
	return (mini.last_status);
}
