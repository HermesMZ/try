
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_bsq
{
	int		lines;
	int		len;
	char	**grid;
	char	empty;
	char	obstacle;
	char	full;
}	t_bsq;

void	free_grid(char **grid)
{
	int	i = 0;

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

int	check_line(char *line, t_bsq *bsq)
{
	int	i = 0;

	while (line[i] && line[i] != '\n')
	{
		if (line[i] != bsq->empty
			&& line[i] != bsq->obstacle)
			return (fprintf(stderr, "chars maperror\n"), 1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i = 0;
	char	*tmp = NULL;

	tmp = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

int	parse_file(FILE *file, t_bsq *bsq)
{
	char	*line = NULL;
	int		bytes_read = 0;
	size_t	len = 0;
	int		i = 0;

	bytes_read = getline(&line, &len, file);
	if (bytes_read == -1)
		return (1);
	line[bytes_read] = '\0';
	bsq->full = line[bytes_read - 2];
	bsq->obstacle = line[bytes_read - 3];
	bsq->empty = line[bytes_read - 4];
	line[bytes_read - 4] = '\0';
	bsq->lines = atoi(line);

	if (bsq->lines == 0
		|| bsq->empty == bsq->obstacle
		|| bsq->empty == bsq->full
		|| bsq->full == bsq->obstacle)
		return (fprintf(stderr, "params maperror\n"), 1);

	bsq->grid = calloc(bsq->lines + 1, sizeof(char *));
	if (!bsq->grid)
		return (fprintf(stderr, "gridalloc maperror\n"), 1);

	while ((bytes_read = getline(&line, &len, file)) != -1)
	{
		if (bsq->len == 0)
			bsq->len = bytes_read;
		else if (bsq->len != bytes_read)
			return (free(line), fprintf(stderr, "line len maperror\n"), 1);
		line[bytes_read] = '\0';
		if (line[bytes_read - 1] != '\n')
			return (free(line), fprintf(stderr, "new line maperror\n"), 1);
		if (check_line(line, bsq) == 1)
			return (free(line), fprintf(stderr, "check line maperror\n"), 1);
		bsq->grid[i] = ft_strdup(line);
		if (!bsq->grid[i])
			return (free(line), fprintf(stderr, "strdup maperror\n"), 1);
		i++;
	}
	if (bsq->lines != i)
		return (free(line), fprintf(stderr, "lines num maperror\n"), 1);
	return (free(line), 0);
}

void	fill_square(t_bsq *bsq, int line, int col, int size)
{
	int	i;
	int	j;

	i = line;
	while (i <= line + size)
	{
		j = col;
		while (j <= col + size)
		{
			bsq->grid[i][j] = bsq->full;
			j++;
		}
		i++;
	}
}

int	check_square(t_bsq *bsq, int line, int col, int size)
{
	int	i;
	int	j;

	i = line;
	while (i < line + size)
	{
		j = col;
		while (j < col + size && bsq->grid[i][j] != '\n')
		{
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
	int	i;

	i = 0;
	while (i < bsq->lines)
	{
		fprintf(stdout, "%s", bsq->grid[i]);
		i++;
	}
}

void	run_bsq(t_bsq *bsq)
{
	int	i;
	int	j;
	int	size = 0;

	size = bsq->lines > bsq->len - 1 ? bsq->len - 1 : bsq->lines;
	while (size > 0)
	{
		i = 0;
		while (i < bsq->lines - size)
		{
			j = 0;
			while (j < bsq->len - 1 - size)
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
	t_bsq	*bsq;
	FILE	*file;

	bsq = calloc(1, sizeof(t_bsq));
	if (!bsq)
		return (1);
	file = argc == 1 ? stdin : fopen(argv[1], "r");
	if (!file)
		return (1);
	if (parse_file(file, bsq) == 1)
	{
		if (file != stdin)
			fclose(file);
		return (free_bsq(bsq), 1);
	}
	if (file != stdin)
		fclose(file);
	printf("empty:%c, obstacle:%c, full:%c, lines:%d\n", bsq->empty, bsq->obstacle, bsq->full, bsq->lines);
	run_bsq(bsq);
	print_bsq(bsq);
	return (free_bsq(bsq), 0);

}
