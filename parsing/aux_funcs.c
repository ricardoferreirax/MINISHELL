/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:08:08 by pfreire-          #+#    #+#             */
/*   Updated: 2025/10/01 11:53:40 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MiNyanShell.h"
#include "parsing.h"


bool	forbidden_instruction(char *str, int i)
{
	if (str[i] == '&')
	{
		if (str[i + 1] == '&')
			return (true);
	}
	else if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			return (true);
	}
	else if (str[i] == '*')
	{
		return (true);
	}
	return (false);
}


char	*skip_whitespaces(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (str);
}

int arr_size(void **arr)
{
    int i;

    i = 0;
    if (!arr) 
        return (0);
    while (arr[i]) 
        i++;
    return (i);
}

t_cmd *cmd_new(void)  // cria um nó de comando (um elemento da pipeline!)
{
    t_cmd *cmd = (t_cmd *)calloc(1, sizeof(*cmd));
    if (!cmd) 
        return (NULL);
    cmd->head = NULL;
    cmd->next = NULL;
    // cmd->pipe = false;
    return (cmd);
}
