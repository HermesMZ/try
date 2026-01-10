/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:59:29 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/11 13:07:41 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

bool	check_line_chars(const char *line, t_bsq *bsq)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != bsq->empty && line[i] != bsq->obstacle)
			return (false);
		i++;
	}
	return (true);
}

int	check_line(char *line, t_bsq *bsq, char **lines, int line_len)
{
	int	tmp;

	tmp = 0;
	if (!check_line_chars(line, bsq))
	{
		free_lines(lines);
		free(line);
		return (false);
	}
	if (line_len == 0)
		line_len = ft_strlen(line);
	tmp = ft_strlen(line);
	if (tmp != line_len)
	{
		free_lines(lines);
		free(line);
		return (false);
	}
	return (line_len);
}

bool	check_file(char *filename, t_bsq *bsq)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (file == NULL)
		return (perror("Error opening file"), false);
	if (fscanf(file, "%u %c %c %c\n", &bsq->lines, &bsq->empty, &bsq->obstacle,
			&bsq->full) != 4)
		return (fclose(file), false);
	if (bsq->lines == 0 || bsq->empty == bsq->obstacle
		|| bsq->empty == bsq->full || bsq->obstacle == bsq->full)
		return (fclose(file), false);
	if (!parse_lines(file, bsq))
		return (fclose(file), false);
	fclose(file);
	return (true);
}

bool	check_stdin(t_bsq *bsq)
{
	if (fscanf(stdin, "%u %c %c %c\n", &bsq->lines, &bsq->empty, &bsq->obstacle,
			&bsq->full) != 4)
		return (false);
	if (bsq->lines == 0 || bsq->empty == bsq->obstacle
		|| bsq->empty == bsq->full || bsq->obstacle == bsq->full)
		return (false);
	if (!parse_lines(stdin, bsq))
		return (false);
	return (true);
}

