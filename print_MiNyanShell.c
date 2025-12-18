/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_MiNyanShell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:22:29 by pfreire-          #+#    #+#             */
/*   Updated: 2025/12/18 11:42:23 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/MiNyanShell.h"

void print_chararr(char **arr)
{
	int i = 0;
	if(!arr)
		return;
	while(arr[i])
	{
		ft_printf("%s", arr[i]);
		i++;
	}
}

int print_MiNyanShell(void)
{
	char **arr = malloc(sizeof(char *) * 24 + 1);
	int fd = open("MiNyanShell.txt", O_RDONLY);
	if(fd < 0)
		return -1;
	int i = 0;
	char *line;
	while(i < 24)
	{
		line = get_next_line(fd);
		if(!line)
		{
			if(arr)
				free_2d((void **)arr);
			return -1;
		}
		arr[i] = ft_strdup(line);
		free(line);
		if(!arr[i])
		{
			arr[i] = NULL;
			if(arr)
				free_2d((void **)arr);
			return -1;
		}
		i++;
		arr[i] = NULL;
	}
	arr[i] = NULL;
	print_chararr(arr);
	if(arr)
		free_2d((void**)arr);
	return 0;
}
