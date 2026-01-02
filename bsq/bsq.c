/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:36:45 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/02 18:03:15 by mzimeris         ###   ########.fr       */
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

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	tmp = calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

int	check_lines(t_bsq *bsq, FILE *file)
{
	size_t	i;
	char	*line;
	size_t	len;
	int		bytes_read;

	bsq->grid = calloc(bsq->lines + 1, sizeof(char *));
	if (!bsq->grid)
		return (1);
	i = 0;
	len = 0;
	line = NULL;
	while (i < bsq->lines)
	{
		bytes_read = getline(&line, &len, file);
		if (bytes_read == -1)
			return (1);
		printf("line = %s\n", line);
		if (bsq->cols == 0)
			bsq->cols = ft_strlen(line) - 1;
		if (bsq->cols != ft_strlen(line) - 1)
			return (1);
		bsq->grid[i] = ft_strdup(line);
		if (!bsq->grid[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_cell(t_bsq *bsq, size_t line, size_t col, size_t size)
{
	size_t	i;
	size_t	j;

	printf("line = %zu, col = %zu, size = %zu, %d, %d\n", line, col, size, bsq->lines, bsq->cols);
	
	i = line;
	while (i < line + size)
	{
		printf("check_cell\n");
		j = col;
		while (j < col + size)
		{
			printf("i = %zu, j = %zu, size = %zu, %d\n", i, j, size,bsq->cols);
			if (bsq->grid[i][j] == bsq->obstacle)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	print_bsq(t_bsq *bsq)
{
	size_t	i;

	i = 0;
	while (bsq->grid[i])
	{
		fprintf(stdout, "%s", bsq->grid[i]);
		i++;
	}
}

void	fill_square(t_bsq *bsq, size_t line, size_t col, size_t size)
{
	size_t	i;
	size_t	j;

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
}

void	run_bsq(t_bsq *bsq)
{
	size_t	size;
	size_t	i;
	size_t	j;

	printf("ruuuuuuuuuuuuuun\n");
	size = (bsq->lines < bsq->cols ? bsq->lines : bsq->cols);
	while (size > 0)
	{
		i = 0;
		while (i <= bsq->lines - size)
		{
			j = 0;
			while (j <= bsq->cols - size)
			{
				if (check_cell(bsq, i, j, size) == 0)
				{
					fill_square(bsq, i, j, size);
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

int	check_in(t_bsq *bsq, FILE *file)
{
	if (fscanf(file, "%d %c %c %c\n", &bsq->lines, &bsq->empty, &bsq->obstacle,
			&bsq->full) != 4)
		return (1);
	if (bsq->lines == 0
		|| bsq->full == bsq->empty
		|| bsq->full == bsq->obstacle
		|| bsq->empty == bsq->obstacle)
		return (1);
	if (check_lines(bsq, file) == 1)
	{
		print_bsq(bsq);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_bsq	*bsq;
	int		i;
	FILE	*file;

	bsq = calloc(1, sizeof(t_bsq));
	if (!bsq)
		return (1);
	if (argc == 1)
	{
		if (check_in(bsq, stdin) == 1)
			return (1);
		run_bsq(bsq);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			if (bsq->grid)
				free_grid(bsq->grid);
			file = fopen(argv[i], "r");
			if (file == NULL)
				continue ;
			if (check_in(bsq, file) == 1)
				return (fprintf(stderr, "map error\n"), fclose(file), 1);
			fclose(file);
			run_bsq(bsq);
			i++;
		}
	}
	free_bsq(bsq);
	return (0);
}
