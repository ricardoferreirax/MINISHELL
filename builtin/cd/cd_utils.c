/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:18:33 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:45:14 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/envyan.h"

int	cd_error(t_mini *mini, char *msg, char *path)
{
	ft_putstr_fd("Minyanshell: Error changing directory: ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
    mini->last_status = 1;
	return (1);
}

char *get_envyan(t_mini *mini, char *key)
{
    t_envyan *node;

    if (!mini || !key)
        return NULL;

    node = mini->envyan;
    while (node)
    {
        if (node->key && strcmp(node->key, key) == 0)
        {
            if (!node->value)
                return (NULL);
            return (ft_strdup(node->value));
        }
        node = node->next;
    }
    return (NULL);
}

