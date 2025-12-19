/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:04:14 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/19 17:54:56 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	print_life(t_life *life)
{
	int	i;
	int	j;

	i = 0;
	while (life->grid[i])
	{
		j = 0;
		// while (life->grid[i][j] == ' ')
		// 	j++;
		while (life->grid[i][j])
		{
			putchar(life->grid[i][j]);
			j++;
		}
		putchar('\n');
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

int	read_input(t_life *life)
{
	unsigned int	i;
	unsigned int	j;
	char			buffer[10000];
	int				bytes_read;
	unsigned int	k;
	int				draw;

	i = 0;
	j = 0;
	k = 0;
	draw = 0;
	bytes_read = read(0, &buffer, 10000);
	if (bytes_read == -1)
		return (1);
	buffer[bytes_read] = '\0';
	while (buffer[k])
	{
		if (buffer[k] == 'x')
		{
			if (!draw)
				draw = 1;
			else
				draw = 0;
		}
		if (buffer[k] == 'w' && i > 0)
			i--;
		if (buffer[k] == 's' && i < life->height - 1)
			i++;
		if (buffer[k] == 'a' && j > 0)
			j--;
		if (buffer[k] == 'd' && j < life->width - 1)
			j++;
		if (draw)
			life->grid[i][j] = 'O';
		// printf("char : %c, draw : %d, i : %d, j : % d\n", buffer[k], draw, i, j);
		k++;
	}
	return (0);
}

char	**new_grid(char **grid, int lines, int cols)
{
	char	**new_grid;
	int		i;
	int		j;

	new_grid = calloc((lines + 1), sizeof(char *));
	if (!new_grid)
		return (NULL);
	new_grid[lines] = NULL;
	i = 0;
	while (grid[i])
	{
		new_grid[i] = calloc((cols + 1), sizeof(char));
		if (!new_grid[i])
			return (free_grid(new_grid), NULL);
		new_grid[i][cols] = '\0';
		j = 0;
		while (j < cols)
		{
			new_grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (new_grid);
}

int		count_cell(t_life *life, unsigned int line, unsigned int col)
{
	int	count;

	count = 0;
	if (line < (life->height - 1) && col > 0 && life->grid[line + 1][col - 1] == 'O')
		count++;
	if (col > 0 && life->grid[line][col - 1] == 'O')
		count++;
	if (line > 0 && col > 0 && life->grid[line -1][col - 1] == 'O')
		count++;
	if (line < (life->height - 1) && col < life->width - 1 && life->grid[line + 1][col + 1] == 'O')
		count++;
	if (col < life->width - 1 && life->grid[line][col + 1] == 'O')
		count++;
	if (line > 0 && col < life->width - 1 && life->grid[line - 1][col + 1] == 'O')
		count++;
	if (line < (life->height - 1) && life->grid[line + 1][col] == 'O')
		count++;
	if (line > 0 && life->grid[line - 1][col] == 'O')
		count++;
	return (count);
}

char	check_cell(t_life *life, unsigned int line, unsigned int col)
{
	int	count;

	count = count_cell(life, line, col);
	if (life->grid[line][col] == ' ')
	{
		if (count == 3)
			return ('O');
		return (' ');
	}
	if (life->grid[line][col] == 'O')
	{
		if (count < 2 || count > 3)
			return (' ');
		return ('O');
	}
	return ('x');
}

char	**iterate(char **new_grid, t_life *life)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < life->height)
	{
		j = 0;
		while (j < life->width)
		{
			new_grid[i][j] = check_cell(life, i, j);
			j++;
		}
		i++;
	}
	return (new_grid);
}

void	run_life(t_life *life)
{
	char			**grid;

	while (life->iteration > 0)
	{
		grid = new_grid(life->grid, life->height, life->width);
		if (!grid)
			return ;
		grid = iterate(grid, life);
		if (!grid)
			return ;
		free_grid(life->grid);
		life->grid = grid;
		life->iteration--;
	}
	print_life(life);
}

int	main(int argc, char *argv[])
{
	t_life			*life;
	unsigned int	i;
	unsigned int	j;

	if (argc != 4)
		return (1);
	life = calloc(1, sizeof(t_life));
	if (!life)
		return (1);
	life->width = atoi(argv[1]);
	life->height = atoi(argv[2]);
	life->iteration = atoi(argv[3]);
	life->grid = calloc((life->height + 1), sizeof(char *));
	if (!life->grid)
		return (1);
	i = 0;
	while (i < life->height)
	{
		life->grid[i] = calloc((life->width + 1), sizeof(char));
		if (!life->grid[i])
			return (1);
		j = 0;
		while (j < life->width)
		{
			life->grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	if (read_input(life) == 1)
		return (1);
	run_life(life);
	free_life(life);
	return (0);
}
