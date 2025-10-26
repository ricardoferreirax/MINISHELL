/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:09:57 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:36:44 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is alphanumeric.
 *
 * Determines whether the given character is a digit (0–9) or an
 * uppercase/lowercase letter (A–Z, a–z).
 *
 * @param a Character to check.
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int	ft_isalnum(char a)
{
	if ((a >= 48 && a <= 57) || (a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return (1);
	else
		return (0);
}
