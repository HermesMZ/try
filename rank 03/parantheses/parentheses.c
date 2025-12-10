/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:14:41 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/31 17:01:28 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

int	find_pair_parentheses(char *str, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;
		if (count == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	print_pair(int len, int open, int close)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i == open)
			write(1, "(", 1);
		else if (i == close)
			write(1, ")", 1);
		else
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	solve(char *str)
{
	int	len;
	int	i;
	int	close;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '(')
		{
			close = find_pair_parentheses(str, i);
			if (close != -1)
				print_pair(len, i, close);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	printf("%s\n", av[1]);
	solve(av[1]);
	return (0);
}
