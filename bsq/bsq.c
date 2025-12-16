/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:41:14 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/16 15:36:19 by mzimeris         ###   ########.fr       */
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
	while (bsq->grid[i])
	{
		fprintf(stdout, "%s\n", bsq->grid[i]);
		i++;
	}
}

int	check_params(t_bsq *bsq)
{
	if (bsq->lines == 0
		|| bsq->empty == bsq->full
		|| bsq->empty == bsq->obstacle
		|| bsq->full == bsq->obstacle)
		return (1);
	if (bsq->empty < 32 || bsq->empty > 126)
		return (1);
	if (bsq->empty < 32 || bsq->empty > 126)
		return (1);
	if (bsq->empty < 32 || bsq->empty > 126)
		return (1);
	return (0);
}

int	ft_strlen(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

char	*ft_strdup(char *line, t_bsq *bsq)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(line);
	if (bsq->cols && len != (int)bsq->cols)
		return (NULL);
	tmp = calloc(sizeof(char), len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		tmp[i] = line[i];
		i++;
	}
	return (tmp);
}

int	check_line(t_bsq *bsq, FILE *file)
{
	char			*line;
	size_t			len;
	unsigned int	cols;
	int				i;

	line = NULL;
	len = 0;
	cols = 0;
	i = 0;
	bsq->grid = calloc(sizeof(char *), bsq->lines + 1);
	if (!bsq->grid)
		return (1);
	while (getline(&line, &len, file) != -1)
	{
		bsq->grid[i] = ft_strdup(line, bsq);
		if (!bsq->grid[i])
			return (free(line), 1);
		if (bsq->cols == 0)
			bsq->cols = ft_strlen(bsq->grid[i]);
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
	if (check_line(bsq, stdin) == 1)
		return (1);
	return (0);
}

int	check_file(t_bsq *bsq, char *filename)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (file == NULL)
		return (fclose(file), 1);
	if (fscanf(file, "%u %c %c %c\n", &bsq->lines, &bsq->empty,
			&bsq->obstacle, &bsq->full) != 4)
		return (fclose(file), 1);
	if (check_params(bsq) == 1)
		return (fclose(file), 1);
	if (check_line(bsq, file) == 1)
		return (fclose(file), 1);
	return (fclose(file), 0);
}

int	check_square(unsigned int line, unsigned int col, unsigned int size, t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;

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
		i++;
	}
	return (0);
}

void	fill_square(unsigned int line, unsigned int col, unsigned int size, t_bsq *bsq)
{
	unsigned int	i;
	unsigned int	j;

	printf("%c%c%c\n", bsq->empty, bsq->obstacle, bsq->full);
	i = line;
	while (i < (bsq->lines - size))
	{
		j = col;
		while (j < (bsq->cols - size))
		{
			bsq->grid[i][j] = bsq->full;
			j++;
		}
		i++;
	}
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
			return (fprintf(stderr, "map error\n"), free_bsq(bsq), 1);
		run_bsq(bsq);
	}
	else
	{
		i = 0;
		while (++i < argc)
		{
			if (bsq->grid)
			{
				free_grid(bsq->grid);
				bsq->lines = 0;
				bsq->cols = 0;
			}
			if (check_file(bsq, argv[i]) == 1)
			{
				fprintf(stderr, "map error\n");
				continue ;
			}
			run_bsq(bsq);
		}
	}
	free_bsq(bsq);
	return (0);
}
