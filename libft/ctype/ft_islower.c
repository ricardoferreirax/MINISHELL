/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:43:27 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:34 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is lowercase.
 *
 * Determines whether the given character is a lowercase letter
 * ('a'–'z').
 *
 * @param c Character to check.
 * @return 1 if the character is lowercase, 0 otherwise.
 */
int	ft_islower(int c)
{
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}
