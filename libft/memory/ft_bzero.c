/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:07:47 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:50:00 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
 * @brief Sets a memory area to zero.
 *
 * @param ptr Pointer to the memory area.
 * @param size Number of bytes to set to zero.
 */
void	ft_bzero(void *a, size_t i)
{
	ft_memset(a, 0, i);
}
