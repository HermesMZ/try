/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:04:53 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/20 17:03:58 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

char	**new_grid(t_life *life)
{
	unsigned int	i;
	unsigned int	j;
	char			**new_grid;

	i = 0;
	new_grid = calloc(life->height + 1, sizeof(char *));
	if (!new_grid)
		return (NULL);
	while (i < life->height)
	{
		new_grid[i] = calloc(life->width + 1, sizeof(char));
		if (!new_grid[i])
			return (NULL);
		j = 0;
		while (j < life->width)
		{
			new_grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (new_grid);
}

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_life(t_life *life)
{
	if (life->grid)
		free_grid(life->grid);
	free(life);
}

void	print_grid(char	**grid)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (grid[i])
	{
		// printf("%s\n", grid[i]);
		j = 0;
		while (grid[i][j])
		{
			putchar(grid[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
}

void	draw_grid(t_life *life)
{
	int				bytes_read;
	char			buffer[10000];
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	int				draw;

	bytes_read = read(0, &buffer, 10000);
	if (bytes_read == -1)
		return ;
	buffer[bytes_read] = '\0';
	i = 0;
	j = 0;
	k = 0;
	draw = 0;
	while (buffer[k])
	{
		if (buffer[k] == 'x')
		{
			if (draw)
				draw = 0;
			else
				draw = 1;
		}
		if (i < life->height - 1 && buffer[k] == 's')
			i++;
		if (i > 0 && buffer[k] == 'w')
			i--;
		if (j > 0 && buffer[k] == 'a')
			j--;
		if (j < (life->width - 1) && buffer[k] == 'd')
			j++;
		if (draw)
			life->grid[i][j] = 'O';
		k++;
	}
}

char	check_cell(t_life *life, unsigned int i, unsigned int j)
{
	int	count;

	count = 0;
	if (i > 0 && life->grid[i - 1][j] == 'O')
		count++;
	if (i > 0 && j > 0 && life->grid[i - 1][j - 1] == 'O')
		count++;
	if (i > 0 && j < (life->width - 1) && life->grid[i - 1][j + 1] == 'O')
		count++;
	if (i < (life->height - 1) && j < (life->width - 1) && life->grid[i + 1][j + 1] == 'O')
		count++;
	if (i < (life->height - 1) && j > 0 && life->grid[i + 1][j - 1] == 'O')
		count++;
	if (i < (life->height - 1) && life->grid[i + 1][j] == 'O')
		count++;
	if (j < (life->width - 1) && life->grid[i][j + 1] == 'O')
		count++;
	if (j > 0 && life->grid[i][j - 1] == 'O')
		count++;
	if (life->grid[i][j] == 'O')
	{
		if (count == 2 || count == 3)
			return ('O');
		else
			return (' ');
	}
	if (life->grid[i][j] == ' ')
	{
		if (count == 3)
			return ('O');
		else
			return (' ');
	}
	return ('X');
}

char	**deathlife(t_life *life, char **iteration)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < life->height)
	{
		j = 0;
		while (j < life->width)
		{
			iteration[i][j] = check_cell(life, i, j);
			j++;
		}
		i++;
	}
	return (iteration);
}

void	iterate(t_life *life)
{
	char **iteration;

	while (life->iteration > 0)
	{
		iteration = new_grid(life);
		if (!iteration)
			return ;
		iteration = deathlife(life, iteration);
		free_grid(life->grid);
		life->grid = iteration;
		life->iteration--;
	}
}

int	main(int argc, char *argv[])
{
	t_life	*life;

	if (argc != 4)
		return (1);
	life = calloc(1, sizeof(t_life));
	if (!life)
		return (1);
	life->width = atoi(argv[1]);
	life->height = atoi(argv[2]);
	life->iteration = atoi(argv[3]);
	life->grid = new_grid(life);
	if (!life->grid)
		return (free_life(life), 1);
	draw_grid(life);
	iterate(life);
	print_grid(life->grid);
	free_life(life);
	return (0);
}
