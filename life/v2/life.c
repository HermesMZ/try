/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:21:00 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/09 19:43:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

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

void	print_life(t_life *life)
{
	int	i;
	int	j;

	i = 0;
	while (i < life->height)
	{
		j = 0;
		while (j <life->width)
		{
			putchar(life->grid[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
}

t_life	*init(char *argv[])
{
	t_life	*life;
	int		i;
	int		j;

	life = calloc(1, sizeof(t_life));
	if (!life)
		return (NULL);
	life->dead = ' ';
	life->live = 'O';
	life->width = atoi(argv[1]);
	life->height = atoi(argv[2]);
	life->iterations = atoi(argv[3]);
	life->grid = calloc(life->height + 1, sizeof(char *));
	if (!life->grid)
		return (free_life(life), NULL);
	i = 0;
	while (i < life->height)
	{
		life->grid[i] = calloc(life->width + 1, sizeof(char));
		if (!life->grid[i])
			return (free_life(life), NULL);
		j = 0;
		while (j < life->width)
		{
			life->grid[i][j] = life->dead;
			j++;
		}
		i++;
	}
	return (life);
}

void	draw(t_life *life)
{
	int		bytes_read;
	char	buffer[1];
	int		draw;
	int		i;
	int		j;

	draw = 0;
	i = 0;
	j = 0;
	bytes_read = read(0, buffer, 1);
	while (bytes_read > 0)
	{
		if (buffer[0] == 'x' && draw)
			draw = 0;
		else if (buffer[0] == 'x' && !draw)
			draw = 1;
		else if (i > 0 && buffer[0] == 'w')
			i--;
		else if (i < life->height - 1 && buffer[0] == 's')
			i++;
		else if (j > 0 && buffer[0] == 'a')
			j--;
		else if (j < life->width - 1 && buffer[0] == 'd')
			j++;
		if (draw)
			life->grid[i][j] = life->live;
		bytes_read = read(0, &buffer, 1);
	}
}

int	alive(t_life *life, int i, int j)
{
	int	count;

	count = 0;
	if (i > 0 && life->grid[i - 1][j] == life->live)
		count++;
	if (j < life->width - 1 && i > 0 && life->grid[i - 1][j + 1] == life->live)
		count++;
	if (j > 0 && i > 0 && life->grid[i - 1][j - 1] == life->live)
		count++;
	if (i < life->height - 1 && life->grid[i + 1][j] == life->live)
		count++;
	if (j < life->width - 1 && i < life->height - 1 && life->grid[i + 1][j + 1] == life->live)
		count++;
	if (j > 0 && i < life->height - 1 && life->grid[i + 1][j - 1] == life->live)
		count++;
	if (j < life->width - 1 && life->grid[i][j + 1] == life->live)
		count++;
	if (j > 0 && life->grid[i][j - 1] == life->live)
		count++;
	return (count);
}

char	death(t_life *life, int i, int j)
{
	int	count;

	count = alive(life, i, j);
	if (life->grid[i][j] == life->live)
	{
		if (count > 3 || count < 2)
			return (life->dead);
	}
	else
	{
		if (count != 3)
			return (life->dead);
	}
	return (life->live);
}

char	**iterate_grid(t_life *life)
{
	char	**new_grid;
	int		i;
	int		j;

	new_grid = calloc(life->height + 1, sizeof(char *));
	if (!new_grid)
		return (free_life(life), NULL);
	i = 0;
	while (i < life->height)
	{
		new_grid[i] = calloc(life->width + 1, sizeof(char));
		if (!new_grid[i])
			return (free_life(life), free_grid(new_grid), NULL);
		j = 0;
		while (j < life->width)
		{
			new_grid[i][j] = death(life, i, j);
			j++;
		}
		i++;
	}
	return (new_grid);
}

void	run(t_life *life)
{
	char	**new_grid;

	new_grid = NULL;
	while (life->iterations-- > 0)
	{
		new_grid = iterate_grid(life);
		if (!new_grid)
		{
			free_life(life);
			return ;
		}
		free_grid(life->grid);
		life->grid = new_grid;
	}
}

int	main(int argc, char *argv[])
{
	t_life	*life;

	if (argc < 4)
		return (1);
	life = init(argv);
	if (!life)
		return (1);
	draw(life);
	run(life);
	print_life(life);
	free_life(life);
	return (0);
}
