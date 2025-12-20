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
#include <stdint.h>
#include <sys/types.h>

void	print_chararr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s", arr[i]);
		i++;
	}
}

uint32_t	hash_file(const char *path)
{
	int				fd;
	ssize_t			read_bytes;
	unsigned char	buf[256];
	uint32_t		hash;
	ssize_t			i;

	hash = 2166136261u;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	read_bytes = read(fd, buf, sizeof(buf));
	while (read_bytes > 0)
	{
		i = 0;
		while (i < read_bytes)
		{
			hash ^= buf[i];
			hash *= 166777619u;
			i++;
		}
		read_bytes = read(fd, buf, sizeof(buf));
	}
	close(fd);
	return (hash);
}

int	print_minyanshell(void)
{
	char	**arr;
	int		fd;
	int		i;
	char	*line;

	fd = open("MiNyanShell.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	arr = ft_calloc(sizeof(char *), 24 + 1);
	if (!arr)
		return (close(fd), -1);
	i = 0;
	while (i < 24)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), -1);
		arr[i] = ft_strdup(line);
		free(line);
		if (!arr[i])
			return (close(fd), -1);
		i++;
	}
	arr[i] = NULL;
	return (print_chararr(arr), close(fd), free_2d((void **)arr), 0);
}
