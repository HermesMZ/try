/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:08:54 by mzimeris          #+#    #+#             */
/*   Updated: 2026/02/16 14:06:38 by mzimeris         ###   ########.fr       */
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	tmp = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	print_grid(t_bsq *bsq)
{
	int	i;

	i = 0;
	while (i < bsq->lines)
	{
		fprintf(stdout, "%s\n", bsq->grid[i]);
		i++;
	}
}

int	line_check(char *line, t_bsq *bsq)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != bsq->empty
			&& line[i] != bsq->obstacle)
			return (1);
		i++;
	}
	return (0);
}

int	parse_file(FILE *file, t_bsq *bsq)
{
	char	*line;
	size_t	len;
	int		bytes_read;
	int		i;

	i = 0;
	line = NULL;
	len = 0;
	bytes_read = 0;
	bytes_read = getline(&line, &len, file);
	line[bytes_read] = '\0';
	if (bytes_read < 4)
		return (fprintf(stderr, "arguments maperror\n"), 1);
	bsq->full = line[bytes_read - 2];
	bsq->obstacle = line[bytes_read - 3];
	bsq->empty = line[bytes_read - 4];
	line[bytes_read - 4] = '\0';
	bsq->lines = atoi(line);
	if (bsq->full == bsq->obstacle
		|| bsq->full == bsq->empty
		|| bsq->empty == bsq->obstacle
		|| bsq->lines == 0)
		return (fprintf(stderr, "bouh maperror\n"), 1);
	bsq->grid = calloc(bsq->lines + 1, sizeof(char *));
	if (!bsq->grid)
		return (fprintf(stderr, "alloc maperror\n"), 1);
	while ((bytes_read = getline(&line, &len, file)) != -1)
	{
		line[bytes_read] = '\0';
		if (line[bytes_read - 1] != '\n')
			return (free(line), fprintf(stderr, "line break maperror\n"), 1);
		if (bsq->len == 0)
			bsq->len = bytes_read;
		else if (bsq->len != bytes_read)
			return (free(line), fprintf(stderr, "check len maperror\n"), 1);
		if (line_check(line, bsq) == 1)
			return (free(line), fprintf(stderr, "line check maperror\n"), 1);
		bsq->grid[i] = ft_strdup(line);
		if (!bsq->grid[i])
			return (free(line), fprintf(stderr, "alloc maperror\n"), 1);
		i++;
	}
	if (i != bsq->lines)
		return (free(line), fprintf(stderr, "check number of lines maperror\n"), 1);

	free(line);
	return (0);
}

int	check_square(t_bsq *bsq, int line, int col, int size)
{
	int	i;
	int	j;

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

void	fill_square(t_bsq *bsq, int line, int col, int size)
{
	int	i;
	int	j;

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
	int	i;
	int	j;
	int	size;

	size = bsq->lines > (bsq->len - 1) ? bsq->len - 1 : bsq->lines;
	while (size > 0)
	{
		i = 0;
		while (i < bsq->lines)
		{
			j = 0;
			while (j < bsq->len - 1)
			{
				if (check_square(bsq, i, j, size) == 0)
				{
					fill_square(bsq, i, j, size);
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
	FILE	*file;
	t_bsq	*bsq;

	bsq = calloc(1, sizeof(t_bsq));
	if (!bsq)
		return (fprintf(stderr, "alloc error\n"), 1);

	if (argc == 1)
	{
		file = stdin;
		if (parse_file(file, bsq) == 1)
			return (free_bsq(bsq), 1);
	}
	else if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (!file)
			return (fprintf(stderr, "fail to open file\n"), 1);
		if (parse_file(file, bsq) == 1)
			return (free_bsq(bsq), fclose(file), 1);
		fclose(file);
	}
	else
		return (fprintf(stderr, "send no more than one file\n"), 1);
	run_bsq(bsq);
	print_grid(bsq);
	return (free_bsq(bsq), 0);
	
}
