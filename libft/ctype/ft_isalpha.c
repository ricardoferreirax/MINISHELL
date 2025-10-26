/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:44:21 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:36:53 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is alphabetic.
 *
 * Determines whether the given character is an uppercase or lowercase
 * letter (A–Z, a–z).
 *
 * @param a Character to check.
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
int	ft_isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	return (0);
}
