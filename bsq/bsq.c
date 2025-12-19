/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:36:35 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/17 11:49:10 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

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

void	free_bsq(t_bsq *bsq)
{
	if (bsq->grid)
		free_grid(bsq->grid);
	free(bsq);
}

void	print_bsq(t_bsq *bsq)
{
	int	i;

	i = 0;
	printf("lines: %u, cols: %u\n", bsq->lines, bsq->cols);
	printf("empty: %c, obstacle: %c, full: %c\n", bsq->empty, bsq->obstacle, bsq->full);
	while (bsq->grid[i])
	{
		fprintf(stdout, "%s\n", bsq->grid[i]);
		i++;
	}
}

int check_params(t_bsq *bsq)
{
	if (bsq->lines == 0
		|| bsq->empty == bsq->obstacle
		|| bsq->empty == bsq->full
		|| bsq->full == bsq->obstacle)
		return (1);
	if (bsq->empty < 32 || bsq->empty > 126
		|| bsq->full < 32 || bsq->full > 126
		|| bsq->obstacle < 32 || bsq->obstacle > 126)
		return (1);
	return (0);
}

size_t	ft_strlen(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		i++;
	}
	return (i);
}

char	*linedup(char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = calloc(sizeof(char), (ft_strlen(line) + 1));
	if (!tmp)
		return (NULL);
	while (line[i] && line[i] != '\n')
	{
		tmp[i] = line[i];
		i++;
	}
	return (tmp);
}

int	check_lines(t_bsq *bsq, FILE *file)
{
	char	*line;
	size_t	len;
	int		i;

	line = NULL;
	len = 0;
	i = 0;
	bsq->grid = calloc(sizeof(char *), (bsq->lines + 1));
	if (!bsq->grid)
		return (1);
	bsq->grid[bsq->lines] = NULL;
	while (getline(&line, &len, file) != -1)
	{
		if (bsq->cols == 0)
			bsq->cols = ft_strlen(line);
		if (ft_strlen(line) != bsq->cols)
			return (free(line), fprintf(stderr, "invalid map\n"), 1);
		bsq->grid[i] = linedup(line);
		if (!bsq->grid[i])
			return (free(line), 1);
		i++;
	}
	free(line);
	return (0);
}

int	check_in(t_bsq *bsq)
{
	if (fscanf(stdin, "%u %c %c %c\n", &bsq->lines, &bsq->empty,
			&bsq->obstacle, &bsq->full) != 4)
		return (1);
	if (check_params(bsq) == 1)
		return (1);
	if (check_lines(bsq, stdin) == 1)
		return (1);
	return (0);
}

int check_file(t_bsq *bsq, char *argv)
{
	FILE	*file;

	file = fopen(argv, "r");
	if (!file)
		return (1);
	if (fscanf(file, "%u %c %c %c\n", &bsq->lines, &bsq->empty,
			&bsq->obstacle, &bsq->full) != 4)
		return (fclose(file), 1);
	if (check_params(bsq) == 1)
		return (fclose(file), 1);
	if (check_lines(bsq, file) == 1)
		return (fclose(file), 1);
	return (fclose(file), 0);
}

int	fill_square(unsigned int line, unsigned int col, unsigned int size, t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;

	i = line;
	while (i < line + size)
	{
		j = col;
		while (j < col + size)
		{
			bsq->grid[i][j] = bsq->full;
			j++;
		}
		i++;
	}
	return (0);
}

int	check_square(unsigned int line, unsigned int col, unsigned int size, t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;

	i = line;
	while (i < line + size)
	{
		j = col;
		while (j < col + size)
		{
			if (bsq->grid[i][j] == bsq->obstacle)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	run_bsq(t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	size = (bsq->lines > bsq->cols) ? bsq->cols : bsq->lines;
	while (size > 0)
	{
		i = 0;
		while (i <= (bsq->lines - size))
		{
			j = 0;
			while (j <= (bsq->cols - size))
			{
				if (check_square(i, j, size, bsq) == 0)
				{
					fill_square(i, j, size, bsq);
					print_bsq(bsq);
					return ;
				}
				j++;
			}
			i++;
		}
		size--;
	}
	print_bsq(bsq);
}

int	main(int argc, char *argv[])
{
	t_bsq	*bsq;
	int		i;

	bsq = malloc(sizeof(t_bsq));
	if (!bsq)
		return (1);
	*bsq = (t_bsq){0};
	if (argc == 1)
	{
		if (check_in(bsq) == 1)
			return (fprintf(stderr, "invalid map\n"), 1);
		run_bsq(bsq);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			if (bsq->grid)
			{
				free_grid(bsq->grid);
				bsq->lines = 0;
				bsq->cols = 0;
			}
			if (check_file(bsq, argv[i]) == 1)
				fprintf(stderr, "invalid map\n");
			else
				run_bsq(bsq);
			i++;
		}
	}
	free_bsq(bsq);
	return (0);
}
