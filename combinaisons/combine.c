/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:07:57 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/31 14:38:55 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

int	find_smallest_index(char *str, int start)
{
	int	i;
	int	smallest_index;

	i = start;
	smallest_index = start;
	while (str[i])
	{
		if (str[i] < str[smallest_index])
			smallest_index = i;
		i++;
	}
	return (smallest_index);
}

void	swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_input(char *input)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	while (i < len - 1)
	{
		j = find_smallest_index(input, i);
		swap(&input[i], &input[j]);
		i++;
	}
}

int	is_in_output(char c, char *output, int out_len)
{
	int	i;

	if (!output)
		return (0);
	i = 0;
	while (i < out_len)
	{
		if (output[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	combine(char *input, char *output, int index)
{
	int	i;
	int	len;

	len = ft_strlen(input);
	// condition d'arrêt
	if (index == len)
	{
		output[index] = '\0';
		write(1, output, len);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	// boucle pour chaque caractère
	while (i < len)
	{
		// si le caractère n'est pas déjà dans output on l'ajoute
		if (!is_in_output(input[i], output, index))
		{
			output[index] = input[i];
			combine(input, output, index + 1);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		len;
	char	*output;

	if (argc != 2)
		return (1);
	// tri de l'entrée
	sort_input(argv[1]);
	len = ft_strlen(argv[1]);
	// malloc pour output
	output = (char *)malloc(len + 1);
	if (!output)
		return (1);
	output[0] = '\0';
	// génération des combinaisons
	combine(argv[1], output, 0);
	free(output);
	return (0);
}
