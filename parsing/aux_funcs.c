/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:08:08 by pfreire-          #+#    #+#             */
/*   Updated: 2025/11/17 12:20:21 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	forbidden_actions(char *str)
{
	int		i;
	bool	inquote;
	bool	indquote;

	if (!str)
		return (true);
	i = 0;
	indquote = false;
	inquote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (!indquote && !indquote)
		{
			if (str[i] == '&' || (str[i] == '|' && str[i + 1] == '|'))
				return (true);
		}
		i++;
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

void	sneaky_print(const char *str)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (str[i] == '\0')
		{
			if (str[i + 1] == '\0')
			{
				break ;
			}
			else if (str[i + 1] == 1)
			{
				ft_putchar(str[i]);
				break ;
			}
		}
		putchar(str[i]);
		i++;
	}
}
