/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:05:54 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:37:05 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is a digit.
 *
 * Determines whether the given character represents a decimal digit
 * ('0'–'9').
 *
 * @param i Character to check.
 * @return 1 if the character is a digit, 0 otherwise.
 */
int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}
