/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:50:07 by pfreire-          #+#    #+#             */
/*   Updated: 2025/08/19 11:46:19 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			i = read(fd, buffer, BUFFER_SIZE);
			if (i <= 0)
				break ;
			buffer[i] = '\0';
		}
		if (ft_strchr(buffer, '\n'))
			return (isolate_line(line, buffer));
		line = gnl_strjoin(line, buffer);
		buffer[0] = '\0';
	}
	if (i < 0)
		return (free(line), NULL);
	return (line);
}
