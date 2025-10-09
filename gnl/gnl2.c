/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:49:53 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/04 14:50:36 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	next_line_length(char *buffer, int start)
{
	int	i;

	i = start;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i - start);
		i++;
	}
	return (i -start);
}

char	*get_next_line(int fd)
{
	static char	buffer[100000];
	static int	bytes_read = -1;
	char		*line;
	int			i = 0;
	static int	start = 0;

	if (bytes_read == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - BUFFER_SIZE + 100000);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
	}
	line = malloc(sizeof(char) * (next_line_length(buffer, start) + 1));
	if (!line);
		return (NULL);
		
	return (0);
}
