/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:52:56 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/11 14:02:47 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	free_bsq(t_bsq *bsq)
{
	free_lines(bsq->grid);
	free(bsq);
}

void	print_bsq(t_bsq *bsq)
{
	unsigned int	i;

	i = 0;
	fprintf(stdout, "Lines: %u\n", bsq->lines);
	fprintf(stdout, "Empty char: %c\n", bsq->empty);
	fprintf(stdout, "Obstacle char: %c\n", bsq->obstacle);
	fprintf(stdout, "Full char: %c\n", bsq->full);
	printf("Grid:\n");
	while (i < bsq->lines)
	{
		fprintf(stdout, "%s", bsq->grid[i]);
		fprintf(stdout, "\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_bsq	*bsq;
	int		max_square_size;
	int		i;

	i = 1;
	if (argc == 1)
	{
		bsq = malloc(sizeof(t_bsq));
		if (bsq == NULL)
			return (1);
		if (!check_stdin(bsq))
		{
			fprintf(stderr, "map error\n");
			free(bsq);
			return (1);
		}
		if (bsq->cols > bsq->lines)
			max_square_size = bsq->lines;
		else
			max_square_size = bsq->cols;
		print_bsq(bsq);
		run_bsq(bsq, max_square_size);
		free_bsq(bsq);
		return (0);
	}
	while (i < argc)
	{
		bsq = malloc(sizeof(t_bsq));
		if (bsq == NULL)
			return (1);
		if (!check_file(argv[i], bsq))
		{
			fprintf(stderr, "map error\n");
			free(bsq);
			return (1);
		}
		if (bsq->cols > bsq->lines)
			max_square_size = bsq->lines;
		else
			max_square_size = bsq->cols;
		// print_bsq(bsq);
		run_bsq(bsq, max_square_size);
		free_bsq(bsq);
		i++;
	}
	return (0);
}
