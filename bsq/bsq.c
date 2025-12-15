/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:29:17 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/15 18:34:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	free_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
	{
		free(grid[i]);
		grid[i] = NULL;
	}
	free(grid);
	grid = NULL;
}

void	free_bsq(t_bsq *bsq)
{
	if (bsq->grid)
		free_grid(bsq->grid);
	free(bsq);
	bsq = NULL;
}

int	parse_line(FILE *file, t_bsq *bsq)
{
	char	*line;
	char	**new_grid;
	size_t	len;
	size_t	tmp;
	int		i;

	line = NULL;
	len = 0;
	tmp = 0;
	new_grid = malloc(sizeof(char *) * (bsq->lines + 1));
	if (!new_grid)
		return (free_bsq(bsq), 1);
	new_grid[bsq->lines] = NULL;
	i = 0;
	while (getline(&line, &len, file) != -1)
	{
		size_t line_len = 0;
		while (line[line_len] && line[line_len] != '\n')
			line_len++;
		if (tmp != 0 && line_len != tmp)
			return (free(line), free_bsq(bsq), 1);
		new_grid[i] = malloc(sizeof(char) * (line_len + 1));
		if (!new_grid[i])
			return (free(line), free_bsq(bsq), 1);
		new_grid[i][line_len] = '\0';
		ft_strcpy(new_grid[i], line);
		if (tmp == 0)
		{
			tmp = line_len;
			bsq->cols = line_len;
		}
		i++;
	}
	free(line);
	bsq->grid = new_grid;
	return (0);
}

int	check_in(t_bsq *bsq)
{
	if (fscanf(stdin, "%u %c %c %c\n", &bsq->lines, &bsq->empty, &bsq->obstacle,
			&bsq->full) != 4)
		return (free_bsq(bsq), 1);
	if (bsq->lines == 0 || bsq->empty == bsq-> obstacle
		|| bsq->obstacle == bsq->full || bsq->empty == bsq->full)
		return (free_bsq(bsq), 1);
	if (parse_line(stdin, bsq) == 1)
		return (free_bsq(bsq), 1);
	return (0);
}


int	check_file(t_bsq *bsq, char *argv)
{
	FILE	*file;

	file = fopen(argv, "r");
	if (file == NULL)
		return (free_bsq(bsq), 1);
	if (fscanf(file, "%u %c %c %c\n", &bsq->lines, &bsq->empty, &bsq->obstacle,
			&bsq->full) != 4)
		return (fclose(file), free_bsq(bsq), 1);
	if (bsq->lines == 0 || bsq->empty == bsq-> obstacle
		|| bsq->obstacle == bsq->full || bsq->empty == bsq->full)
		return (fclose(file), free_bsq(bsq), 1);
	if (parse_line(file, bsq) == 1)
		return (fclose(file), free_bsq(bsq), 1);
	return (fclose(file), 0);
}

void	print_bsq(t_bsq *bsq)
{
	unsigned int	i;

	fprintf(stdout, "\nlines:%u empty:%c obstacle:%c full:%c\n", bsq->cols, bsq->empty,
		bsq->obstacle,
		bsq->full);
	i = 0;
	while (i < bsq->lines)
	{
		fprintf(stdout, "%s", bsq->grid[i]);
		i++;
	}
	fprintf(stdout, "\n");

}

char	**copy_grid(t_bsq *bsq)
{
	char	**new_grid;
	unsigned int		i;

	new_grid = malloc(sizeof(char *) * (bsq->lines + 1));
	if (!new_grid)
		return (free_bsq(bsq), NULL);
	new_grid[bsq->lines] = NULL;
	i = 0;
	while (i < bsq->lines)
	{
		new_grid[i] = malloc(sizeof(char) * (bsq->cols + 1));
		if (!new_grid[i])
			return (free_grid(new_grid), free_bsq(bsq), NULL);
		new_grid[i][bsq->cols] = '\0';
		ft_strcpy(new_grid[i], bsq->grid[i]);
		i++;
	}
	return (new_grid);
}

int		check_square(int col, int line, int size, t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < bsq->lines && j < bsq->cols && bsq->grid[i][j])
	{
		i = line;
		while (i < (bsq->lines - size))
		{
			j = col;
			while (j < (bsq->cols - size))
			{
				if (bsq->grid[i][j] == bsq->obstacle)
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	fill_square(int col, int line, int size, t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (bsq->grid[i][j] && i < bsq->lines && j < bsq->cols)
	{
		i = line;
		while (i < (bsq->lines - size))
		{
			j = col;
			while (j < (bsq->cols - size))
			{
				bsq->grid[i][j] = bsq->full;
				j++;
			}
		}
		i++;
	}
}

void	run_bsq(t_bsq *bsq)
{
	unsigned int	max_square;
	unsigned int	line;
	unsigned int	col;

	line = 0;
	col = 0;
	if (bsq->lines > bsq->cols)
		max_square = bsq->cols;
	else
		max_square = bsq->lines;
	while (max_square > 0)
	{
		line = 0;
		while (line < (bsq->lines - max_square))
		{
			col = 0;
			while (col < (bsq->cols - max_square))
			{
				if (check_square(col, line, max_square, bsq) == 0)
				{
					fill_square(col, line, max_square, bsq);
					print_bsq(bsq);
					return ;
				}
				col++;
			}
			line++;
		}
		max_square--;
	}
	print_bsq(bsq);
}

int	main(int argc, char *argv[])
{
	t_bsq	*bsq;
	int		i;

	i = 0;
	bsq = malloc(sizeof(t_bsq));
	if (!bsq)
		return (1);
	bsq->grid = NULL;
	if (argc == 1)
	{
		if (check_in(bsq) == 1)
			return (1);
		run_bsq(bsq);
	}
	else
	{
		while (++i < argc)
		{
			if (bsq->grid)
				free_grid(bsq->grid);
			if (check_file(bsq, argv[i]) == 1)
				return (1);
			run_bsq(bsq);
		}
	}
	free_bsq(bsq);
	return (0);
}
