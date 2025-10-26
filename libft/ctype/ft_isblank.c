/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:24:55 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:30 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is a blank character.
 *
 * Determines whether the given character is a space (' ') or a
 * horizontal tab ('\t', ASCII 9).
 *
 * @param c Character to check.
 * @return 1 if the character is a blank, 0 otherwise.
 */
int	ft_isblank(int c)
{
	if (c == ' ' || c == 9)
		return (1);
	return (0);
}
