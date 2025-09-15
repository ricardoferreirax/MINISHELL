/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:53:32 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 14:34:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputstr(int out, char *str, int *n)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_dputstr(out, "(null)", n);
		return ;
	}
	while (str[i] != '\0')
	{
		ft_dputchar(out, str[i], n);
		i++;
	}
}
