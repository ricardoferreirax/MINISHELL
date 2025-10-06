/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envyan_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:29:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/06 02:37:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MiNyanShell.h"
#include "../include/envyan.h"

t_envyan	*create_envyan_node(char *key, char *value)
{
	t_envyan	*new_node;

	new_node = malloc(sizeof(t_envyan));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

char *envyan_get_value(t_envyan *head, char *key)
{
    t_envyan *cur;

    if (!key)
        return (NULL);
    cur = head;
    while (cur)
    {
        if (cur->key && ft_strcmp(cur->key, key) == 0)
            return (cur->value);
        cur = cur->next;
    }
    return (NULL);
}

void	cleanup_env_array(char **env_array, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	numberlen(int num)
{
	int			len;
	long		n;

	n = num;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*number;
	long		nbr;

	nbr = n;
	len = numberlen(nbr);
	number = malloc(sizeof(char) * (len + 1));
	if (!number)
		return (NULL);
	if (nbr == 0)
		number[0] = '0';
	if (nbr < 0)
	{
		number[0] = '-';
		nbr = -nbr;
	}
	number[len--] = '\0';
	while (len >= 0 && nbr > 0)
	{
		number[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (number);
}