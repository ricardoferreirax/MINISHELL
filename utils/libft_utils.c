/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:26:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/10/08 17:00:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	idx;

	idx = 0;
	if (!s || fd < 0)
		return ;
	while (s[idx] != '\0')
		write(fd, &s[idx++], 1);
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	idx;

	if (!s || fd < 0)
		return ;
	idx = 0;
	while (s[idx] != '\0')
		write(fd, &s[idx++], 1);
}

void free_chararr(char **arr)
{
    int i;

    if (!arr) return;
    i = 0;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

