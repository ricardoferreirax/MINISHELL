/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:52:17 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:03:36 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is uppercase.
 *
 * Determines whether the given character is an uppercase letter
 * ('A'–'Z').
 *
 * @param c Character to check.
 * @return 1 if the character is uppercase, 0 otherwise.
 */
int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
