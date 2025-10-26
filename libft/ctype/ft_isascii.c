/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:20:49 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:36:59 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a value is a valid ASCII character.
 *
 * Determines whether the given integer falls within the ASCII range
 * (0–127 inclusive).
 *
 * @param a Integer value to check.
 * @return 1 if the value is a valid ASCII character, 0 otherwise.
 */
int	ft_isascii(int a)
{
	if (a >= 0 && a <= 127)
		return (1);
	else
		return (0);
}
