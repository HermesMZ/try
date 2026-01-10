/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:36:35 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/20 19:19:29 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	free_grid(t_bsq *bsq)
{
	unsigned int	i;

	i = 0;
	while (i < bsq->lines)
	{
		free(bsq->grid[i]);
		i++;
	}
	free(bsq->grid);
}

void	free_bsq(t_bsq *bsq)
{
	if (bsq->grid)
		free_grid(bsq);
	free(bsq);
}

void	print_bsq(t_bsq *bsq)
{
	unsigned int	i;

	i = 0;
	while (i < bsq->lines && bsq->grid[i])
	{
		fprintf(stdout, "%s\n", bsq->grid[i]);
		i++;
	}
	fprintf(stdout, "\n");
}

unsigned int	ft_linelen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

int	check_grid(t_bsq *bsq, FILE *file)
{
	unsigned int	i;
	size_t			len;

	i = 0;
	len = 0;
	while (i < bsq->lines && getline(&bsq->grid[i], &len, file) != -1)
	{
		if (bsq->cols == 0)
			bsq->cols = ft_linelen(bsq->grid[i]);
		bsq->grid[i][bsq->cols] = '\0';
		if (bsq->cols != ft_linelen(bsq->grid[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_in(t_bsq *bsq)
{
	if (fscanf(stdin, "%d %c %c %c\n", &bsq->lines, &bsq->empty,
			&bsq->obstacle, &bsq->full) != 4)
		return (1);
	if ((bsq->empty < 32 || bsq->empty > 126)
		|| (bsq->obstacle < 32 || bsq->obstacle > 126)
		|| (bsq->full < 32 || bsq->full > 126))
		return (1);
	if (bsq->lines == 0
		|| bsq->empty == bsq->full
		|| bsq->empty == bsq->obstacle
		|| bsq->obstacle == bsq->full)
		return (1);
	bsq->grid = calloc(bsq->lines + 1, sizeof(char *));
	if (!bsq->grid)
		return (1);
	if (check_grid(bsq, stdin) == 1)
		return (1);
	return (0);
}

int	check_file(t_bsq *bsq, char *argv)
{
	FILE	*file;

	file = fopen(argv, "r");
	if (!file)
		return (1);
	if (fscanf(file, "%d %c %c %c\n", &bsq->lines, &bsq->empty,
			&bsq->obstacle, &bsq->full) != 4)
		return (fclose(file), 1);
	if ((bsq->empty < 32 || bsq->empty > 126)
		|| (bsq->obstacle < 32 || bsq->obstacle > 126)
		|| (bsq->full < 32 || bsq->full > 126))
		return (fclose(file), 1);
	if (bsq->lines == 0 
		|| bsq->empty == bsq->full
		|| bsq->empty == bsq->obstacle
		|| bsq->obstacle == bsq->full)
		return (fclose(file), 1);
	bsq->grid = calloc(bsq->lines + 1, sizeof(char *));
	if (!bsq->grid)
		return (1);
	if (check_grid(bsq, file) == 1)
		return (fclose(file), 1);
	return (fclose(file), 0);
}

void	fill_square(t_bsq *bsq, unsigned int line, unsigned int col, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

printf("break %d %d\n", line, col);

	i = line;
	while (i < (line + size))
	{
		j = col;
		while (j < (col + size))
		{
			bsq->grid[i][j] = bsq->full;
			j++;
		}
		i++;
	}
}

int		check_square(t_bsq *bsq, unsigned int line, unsigned int col, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = line;
	while (i < (line + size))
	{
		j = col;
		while (j < (col + size))
		{

			if (bsq->grid[i][j] == bsq->obstacle)
				return (1);
			j++;
		}
		i++;
	}
	return (fill_square(bsq, line, col, size), 0);
}

void	run_bsq(t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	size = bsq->lines < bsq->cols ? bsq->lines : bsq->cols;
	while (size > 0)
	{
		i = 0;
		while (i <= (bsq->lines - size))
		{
			j = 0;
			while (j <= (bsq->cols - size))
			{
				if (check_square(bsq, i, j, size) == 0)
				{
					print_bsq(bsq);
					return ;
				}
				j++;
			}
			i++;
		}
		size--;
	}
}

int	main(int argc, char *argv[])
{
	t_bsq	*bsq;
	int		i;

	bsq = calloc(1, sizeof(t_bsq));
	if (!bsq)
		return (1);
	if (argc == 1)
	{
		if (check_in(bsq) == 1)
			return (fprintf(stderr, "map error\n"), free_bsq(bsq), 1);
		run_bsq(bsq);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			if (bsq->grid)
			{
				free_grid(bsq);
				*bsq = (t_bsq){0};
			}
			if (check_file(bsq, argv[i]) == 1)
				return (fprintf(stderr, "map error\n"), 1);
			run_bsq(bsq);
			i++;
		}
	}
	free_bsq(bsq);
	return (0);
}
