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

/**
 * @brief Reads the next line from a file descriptor.
 *
 * Reads from the given file descriptor until a newline character (`\n`)
 * or end-of-file is encountered. Returns the line read, including the
 * newline character if present. Uses a static buffer of size `BUFFER_SIZE`
 * to optimize reads.
 *
 * @param fd File descriptor to read from.
 * @return Pointer to a dynamically allocated string containing the line,
 *         or NULL on error or end-of-file.
 *
 * @note The returned string must be freed by the caller.
 * @note `BUFFER_SIZE` can be defined at compile time; defaults to 1.
 */
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	line = NULL;
	i = 0;
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
