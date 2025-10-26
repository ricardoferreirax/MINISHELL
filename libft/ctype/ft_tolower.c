/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:05:00 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:37:17 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Converts an uppercase letter to lowercase.
 *
 * If the given character is an uppercase letter ('A'–'Z'), converts it
 * to the corresponding lowercase letter ('a'–'z'). Otherwise,
	returns it unchanged.
 *
 * @param a Character to convert.
 * @return Lowercase equivalent if uppercase, else the original character.
 */
int	ft_tolower(int a)
{
	if (a >= 'A' && a <= 'Z')
	{
		a += 32;
	}
	return (a);
}
