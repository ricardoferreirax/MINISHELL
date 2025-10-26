/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:27:52 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:38 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is a whitespace character.
 *
 * Determines whether the given character is a whitespace character:
 * space, horizontal tab, newline, vertical tab, form feed, or carriage return.
 *
 * @param c Character to check.
 * @return 1 if the character is whitespace, 0 otherwise.
 */
int	ft_isspace(int c)
{
	if (c == ' ' || c == 9 || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
