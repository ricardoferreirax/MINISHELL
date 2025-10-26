/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:54:34 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:41 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is a hexadecimal digit.
 *
 * Determines whether the given character is a valid hexadecimal digit
 * ('0'–'9', 'A'–'F', 'a'–'f').
 *
 * @param c Character to check.
 * @return 1 if the character is a hexadecimal digit, 0 otherwise.
 */
int	ft_isxdigit(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a'
			&& c <= 'f'))
		return (1);
	return (0);
}
