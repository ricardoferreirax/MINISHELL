/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:57:03 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:37:22 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype.h"

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * If the given character is a lowercase letter ('a'–'z'), converts it
 * to the corresponding uppercase letter ('A'–'Z'). Otherwise,
	returns it unchanged.
 *
 * @param a Character to convert.
 * @return Uppercase equivalent if lowercase, else the original character.
 */
int	ft_toupper(int a)
{
	if (a >= 'a' && a <= 'z')
	{
		a -= 32;
	}
	return (a);
}
