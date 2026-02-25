/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:56:44 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/29 18:03:37 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		putchar(str[i]);
		i++;
	}
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

char	**new_grid(t_life *life)
{
	char	**grid;
	int		i;
	int		j;

	// printf("new grid\n");
	grid = calloc(life->height + 1, sizeof(char *));
	if (!grid)
		return (ft_putstr("grid alloc error\n"), NULL);
	i = 0;
	while (i < life->height)
	{
		grid[i] = calloc(life->width + 1, sizeof(char));
		if (!grid[i])
			return (free_grid(grid), ft_putstr("grid alloc error\n"), NULL);
		j = 0;
		while (j < life->width)
		{
			grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (grid);
}

void	draw_grid(t_life *life, char *input)
{
	int	i;
	int	line;
	int	col;
	int	draw;

	i = 0;
	line = 0;
	col = 0;
	draw = 0;
	while (input[i])
	{
		if (input[i] == 'x')
		{
			if (draw == 0)
				draw = 1;
			else
				draw = 0;
		}
		else if (line > 0 && input[i] == 'w')
			line--;
		else if (line < life->height - 1 && input[i] == 's')
			line++;
		else if (col > 0 && input[i] == 'a')
			col--;
		else if (col < life->width - 1 && input[i] == 'd')
			col++;
		if (draw)
			life->grid[line][col] = 'O';
		i++;
	}
}

void	init_grid(t_life *life)
{
	char	input[100];
	int		bytes_read;

	bytes_read = read(0, input, 100);
	input[bytes_read - 1] = '\0';
	// printf("bouuuuuuuuuuuuuuh\n");
	
	draw_grid(life, input);
	// printf("draw grid ok\n");

}

void	print_grid(t_life *life)
{
	int	i;

	i = 0;
	while (life->grid[i])
	{
		ft_putstr(life->grid[i]);
		putchar('\n');
		i++;
	}
		putchar('\n');

}

int	count(t_life *life, int i, int j)
{
	int	count;

	count = 0;
	if (j < life->width - 1 && i < life->height - 1 && life->grid[i + 1][j + 1] == 'O')
		count++;
	if (j > 0 && i < life->height - 1 && life->grid[i + 1][j - 1] == 'O')
		count++;
	if (i < life->height - 1 && life->grid[i + 1][j] == 'O')
		count++;
	if (j < life->width - 1 && i > 0 && life->grid[i - 1][j + 1] == 'O')
		count++;
	if (j > 0 && i > 0 && life->grid[i - 1][j - 1] == 'O')
		count++;
	if (i > 0 && life->grid[i - 1][j] == 'O')
		count++;
	if (j < life->width - 1 && life->grid[i][j + 1] == 'O')
		count++;
	if (j > 0 && life->grid[i][j - 1] == 'O')
		count++;
	return (count);
}

char	alive(t_life *life, int i, int j)
{
	int	alive;

	alive = count(life, i, j);
	if (alive == 3)
		return ('O');
	else if (life->grid[i][j] == 'O' && alive == 2)
		return ('O');
	else
		return (' ');
}

void	iterate(t_life *life)
{
	int		i;
	int		j;
	char	**grid;

	i = 0;
	grid = new_grid(life);
	while (i < life->height)
	{
		j = 0;
		while (j < life->width)
		{
			grid[i][j] = alive(life, i, j);
			j++;
		}
		i++;
	}
	free_grid(life->grid);
	life->grid = grid;
	print_grid(life);
}

int	main(int argc, char *argv[])
{
	t_life	*life;
	// printf("life\n");

	if (argc != 4)
		return (ft_putstr("wrong number of args\n"), 1);
	life = calloc(1, sizeof(t_life));
	if (!life)
		return (ft_putstr("life alloc error\n"), 1);
	// printf("life alloc ok\n");
	life->width = atoi(argv[1]);
	life->height = atoi(argv[2]);
	life->iteration = atoi(argv[3]);
	life->grid = new_grid(life);
	if (!life->grid)
		return (ft_putstr("grid creation error\n"), 1);
	// printf("life-grid alloc ok\n");
	init_grid(life);
	// printf("init grid ok\n");
	while (life->iteration > 0)
	{
		iterate(life);
		life->iteration--;
	}
	print_grid(life);
	free_life(life);
	return (0);
}
