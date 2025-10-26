/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:37:35 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:37:12 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is printable.
 *
 * Determines whether the given character is printable, including
 * space (' ') but excluding control characters.
 *
 * @param a Character to check.
 * @return 1 if the character is printable, 0 otherwise.
 */
int	ft_isprint(int a)
{
	if (a >= 32 && a <= 126)
		return (1);
	return (0);
}
