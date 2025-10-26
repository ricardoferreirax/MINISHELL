/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:31:16 by pfreire-          #+#    #+#             */
/*   Updated: 2025/09/18 12:02:28 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Checks if a character is a control character.
 *
 * Determines whether the given character is a non-printable control
 * character in the ASCII table (0–31 or 127).
 *
 * @param c Character to check.
 * @return 1 if the character is a control character, 0 otherwise.
 */
int	ft_iscntrl(int c)
{
	if (c < 32 || c == 127)
		return (1);
	return (0);
}
