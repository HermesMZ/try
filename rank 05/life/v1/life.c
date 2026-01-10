/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:49:45 by zoum              #+#    #+#             */
/*   Updated: 2025/12/13 01:46:18 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// atoi, read, putchar, malloc, calloc, realloc, free

#include "life.h"

void	free_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		free(grid[i]);
	free(grid);
}

void	free_life(t_life *life)
{
	free_grid(life->grid);
	free(life);
	return ;
}

t_life	*init_life(char *argv[])
{
	t_life	*life;

	int (i), (j);
	life = malloc(sizeof(t_life));
	if (!life)
		return (NULL);
	i = -1;
	life->width = atoi(argv[1]);
	life->height = atoi(argv[2]);
	life->iteration = atoi(argv[3]);
	life->grid = malloc(sizeof(char *) * (life->height + 1));
	if (!life->grid)
		return (NULL);
	life->grid[life->height] = NULL;
	while (++i < life->height)
	{
		life->grid[i] = malloc(sizeof(char) * (life->width + 1));
		if (!life->grid[i])
			return (free_life(life), NULL);
		j = 0;
		while (j < life->width)
			life->grid[i][j++] = ' ';
		life->grid[i][j] = '\0';
	}
	return (life);
}

void	paint_grid(t_life *life, char *buffer)
{
	int	(i), (col), (line), (draw);
	i = 0;
	col = 0;
	line = 0;
	draw = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'x' && draw)
			draw = 0;
		else if (buffer[i] == 'x' && !draw)
			draw = 1;
		else if (buffer[i] == 'w' && line > 0)
			line--;
		else if (buffer[i] == 's' && line < life->height - 1)
			line++;
		else if (buffer[i] == 'a' && col > 0)
			col--;
		else if (buffer[i] == 'd' && col < life->width - 1)
			col++;
		if (draw)
			life->grid[line][col] = 'O';
		i++;
	}
}

void	print_grid(t_life *life)
{
	int	i;
	int	j;

	i = 0;
	while (life->grid[i])
	{
		j = 0;
		while (life->grid[i][j])
		{
			putchar(life->grid[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
}

int	alive(int i, int j, char **grid, t_life *life)
{
	int	count;

	count = 0;
	if (i + 1 < life->height && grid[i + 1][j] == 'O')
		count++;
	if (i + 1 < life->height && j + 1 < life->width && grid[i + 1][j + 1] == 'O')
		count++;
	if (i + 1 < life->height && j > 0 && grid[i + 1][j - 1] == 'O')
		count++;
	if (i > 0 && grid[i - 1][j] == 'O')
		count++;
	if (i > 0 && j + 1 < life->width && grid[i - 1][j + 1] == 'O')
		count++;
	if (i > 0 && j > 0 && grid[i - 1][j - 1] == 'O')
		count++;
	if (j + 1 < life->width && grid[i][j + 1] == 'O')
		count++;
	if (j > 0 && grid[i][j - 1] == 'O')
		count++;
	return (count);
}

// Une cellule vivante (O) avec 2 ou 3 voisins vivants reste vivante.
// Une cellule vivante avec moins de 2 voisins vivants meurt (sous-population).
// Une cellule vivante avec plus de 3 voisins vivants meurt (surpopulation).
// Une cellule morte avec exactement 3 voisins vivants devient vivante (reproduction).

char	life_dead(int i, int j, char **grid, t_life *life)
{
	int	count;

	count = alive(i, j, grid, life);
	if (grid[i][j] == ' ' && count == 3)
		return ('O');
	else if (grid[i][j] == 'O' && (count == 2 || count == 3))
		return ('O');
	else
		return (' ');
}

int	run_life(t_life *life)
{
	char	**new_grid;
	int		i;
	int		j;

	i = -1;
	new_grid = malloc(sizeof(char *) * (life->height + 1));
	if (!new_grid)
		return (free_life(life), 1);
	new_grid[life->height] = NULL;
	while (++i < life->height)
	{
		new_grid[i] = malloc(sizeof(char) * (life->width + 1));
		if (!new_grid[i])
			return (free_life(life), free_grid(new_grid), 1);
		j = -1;
		while (++j < life->width)
			new_grid[i][j] = life_dead(i, j, life->grid, life);
		new_grid[i][j] = '\0';
	}
	free_grid(life->grid);
	life->grid = new_grid;
	return (0);
}

int	main(int argc, char *argv[])
{
	char	buffer[10000];
	t_life	*life;
	int		i;
	int		bytes_read;

	if (argc != 4)
		return (1);
	life = init_life(argv);
	if (!life)
		return (1);
	bytes_read = read(STDIN_FILENO, buffer, 10000);
	if (bytes_read <= 0)
		return (free_life(life), 1);
	buffer[bytes_read] = '\0';
	paint_grid(life, buffer);
	i = -1;
	while (++i < life->iteration)
		run_life(life);
	print_grid(life);
	free_life(life);
	return (0);
}
