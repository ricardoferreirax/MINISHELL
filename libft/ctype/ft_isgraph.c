/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isgraph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:35:55 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:32 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character has a graphical representation.
 *
 * Determines whether the given character is printable and not a space
 * (i.e., has a visible glyph).
 *
 * @param c Character to check.
 * @return 1 if the character has a graphical representation, 0 otherwise.
 */
int	ft_isgraph(int c)
{
	if (ft_isprint(c) && c != ' ')
		return (1);
	return (0);
}
