/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:46:47 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 16:37:48 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	no_unclosed_quotes(char *str)
{
	bool	inquote;
	bool	indquote;
	int		i;

	inquote = false;
	indquote = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquote)
			inquote = !inquote;
		if (str[i] == '\"' && !inquote)
			indquote = !indquote;
		i++;
	}
	if (indquote || inquote)
		return (false);
	return (true);
}