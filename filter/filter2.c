#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_substr(char *txt, char *filter)
{
	int	i;
	int	filter_len;

	i = 0;
	filter_len = ft_strlen(filter);
	while (i < filter_len)
	{
		if (txt[i] != filter[i])
			return (1);
		i++;
	}
	return (0);
}

int	print_filter(char *filter)
{
	int	i;
	int filter_len;

	i = 0;
	filter_len = ft_strlen(filter);
	while (i++ < filter_len)
		write(1, "*", 1);
	return (filter_len);
}

void	filter(char *txt, char *filter)
{
	int		i;
	int		filter_len;


	if (!filter || filter[0] == '\0')
		write(1, txt, ft_strlen(txt));
	i = 0;
	filter_len = ft_strlen(filter);
	while (txt[i])
	{
		if (!ft_substr(&txt[i], filter))
			i += print_filter(filter);
		else
		{
			write(1, &txt[i], 1);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	char	buffer[100000];
	char	txt[100000];
	int		bytes_read;
	int		i;
	int		j;

	if (argc != 2)
		write(2, "Error: input\n", 13);
	bytes_read = read(0, buffer, 1);
	if (bytes_read < 0)
		write(2, "Error: read\n", 12);
	buffer[bytes_read] = '\0';
	i = 0;
	while (bytes_read)
	{
		j = 0;
		while (j < bytes_read)
			txt[i++] = buffer[j++];
		txt[i] = '\0';
		bytes_read = read(0, buffer, 1);
		if (bytes_read < 0)
			write(2, "Error: read\n", 12);
		buffer[bytes_read] = '\0';
	}
	filter(txt, argv[1]);
	return (0);
}
