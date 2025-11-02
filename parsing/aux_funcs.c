/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:08:08 by pfreire-          #+#    #+#             */
/*   Updated: 2025/11/02 12:32:01 by pfreire-         ###   ########.fr       */
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

