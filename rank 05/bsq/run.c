/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:15:35 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/11 14:02:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

bool	check_square(t_bsq *bsq, int row, int col, int size)
{
	int	i;
	int	j;

	i = row;
	while (i < row + size)
	{
		j = col;
		while (j < col + size)
		{
			if (bsq->grid[i][j] == bsq->obstacle)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	fill_square(t_bsq *bsq, int row, int col, int size)
{
	int	i;
	int	j;

	i = row;
	while (i < row + size)
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

void	run_bsq(t_bsq *bsq, int max_square_size)
{
	unsigned int	size;
	unsigned int	row;
	unsigned int	col;

	size = max_square_size;
	while (size > 0)
	{
		row = 0;
		while (row <= bsq->lines - size)
		{
			col = 0;
			while (col <= bsq->cols - size)
			{
				if (check_square(bsq, row, col, size))
				{
					fill_square(bsq, row, col, size);
					print_bsq(bsq);
					return ;
				}
				col++;
			}
			row++;
		}
		size--;
	}
	print_bsq(bsq);
}
