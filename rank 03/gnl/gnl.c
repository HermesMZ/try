/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:22:36 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/31 17:11:40 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include <stdio.h> // For debugging purposes, can be removed later

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	ft_search(char *str, char c, size_t start)
{
	size_t	i;

	i = start;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	buffer[10000];
	static int	index = 0;
	int			newline_index;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0] == '\0')
	{
		int	bytes_read = read(fd, buffer, 10000);

		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		index = 0; // reset index for new file
	}
	newline_index = ft_search(buffer, '\n', index);
	if (newline_index != -1)
	{
		line = (char *)malloc(newline_index - index + 2);
		if (!line)
			return (NULL);
		line[newline_index - index + 1] = '\0';
		while (buffer[index] && index <= newline_index)
			line[i++] = buffer[index++];
		return (line);
	}
	else if (buffer[index]) // last line without newline
	{
		int	len = ft_strlen(buffer + index);

		line = (char *)malloc(len + 1);
		if (!line)
			return (NULL);
		while (buffer[index] && index < len + index)
			line[i++] = buffer[index++];
		line[i] = '\0';
		return (line);
	}
	else
		return (NULL);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		write(2, "Usage: ./a.out <filename>\n", 26);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error opening file\n", 19);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		write(1, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
