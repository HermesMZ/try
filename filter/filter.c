/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:28:05 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/31 16:05:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strncmp(char *buffer, char *pattern, int size)
{
	int	i;

	i = 0;
	while (buffer[i] && pattern[i] && i < size)
	{
		if (buffer[i] != pattern[i])
			return (buffer[i] - pattern[i]);
		i++;
	}
	if (pattern[i] == '\0')
		return (0);
	return (buffer[i] - pattern[i]);
}

void	filter(char *buffer, char *pattern)
{
	int	i;
	int	j;
	int	pat_len;
	int	buf_len;

	pat_len = ft_strlen(pattern);
	buf_len = ft_strlen(buffer);
	i = 0;
	while (i < buf_len)
	{
		if (ft_strncmp(&buffer[i], pattern, pat_len) == 0)
		{
			j = 0;
			while (j++ < pat_len)
				write(1, "*", 1);
			i += pat_len - 1;
		}
		else
			write(1, &buffer[i], 1);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	char	buffer[10000];
	int		bytes_read;

	if (argc != 2)
		return (write(2, "Error args\n", 12) > 0);
	bytes_read = read(0, buffer, BUFFER_SIZE - BUFFER_SIZE + 10000);
	if (bytes_read < 0)
		return (write(2, "Error reading input\n", 20) > 0);
	buffer[bytes_read] = '\0';
	filter(buffer, argv[1]);
	return (0);
}
