/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:48:13 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:36 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is a punctuation character.
 *
 * Determines whether the given character is printable but not
 * alphanumeric and not a space.
 *
 * @param c Character to check.
 * @return 1 if the character is punctuation, 0 otherwise.
 */
int	ft_ispunct(int c)
{
	if (ft_isprint(c) && (!ft_isalnum(c) && c != ' '))
		return (1);
	return (0);
}
