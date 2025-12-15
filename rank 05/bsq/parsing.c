/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:06:47 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/11 14:01:04 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	add_line(char *line, t_bsq *bsq, char **lines, unsigned int *line_count)
{
	int	line_len;
	int	i;

	line_len = 0;
	line_len = check_line(line, bsq, lines, line_len);
	if (line_len == false)
		return (false);
	if (ft_strlen(line) > 1)
	{
		i = 0;
		while (line[i] != '\0' && line[i] != '\n')
			i++;
		lines[*line_count] = malloc(i + 1);
		if (lines[*line_count] == NULL)
			return (free_lines(lines), free(line), false);
		i = 0;
		while (line[i] != '\0' && line[i] != '\n')
		{
			lines[*line_count][i] = line[i];
			i++;
		}
		lines[*line_count][i] = '\0';
		(*line_count)++;
	}
	return (line_len);
}

bool	parse_lines(FILE *file, t_bsq *bsq)
{
	char				*line;
	size_t				len;
	char				**lines;
	unsigned int		line_count;
	int					line_len;

	line_count = 0;
	line_len = 0;
	line = NULL;
	len = 0;
	lines = malloc(sizeof(char *) * (bsq->lines + 1));
	if (lines == NULL)
		return (false);
	lines[bsq->lines] = NULL;
	while (getline(&line, &len, file) != -1)
		line_len = add_line(line, bsq, lines, &line_count);
	if (line_count != bsq->lines)
		return (free_lines(lines), free(line), false);
	free(line);
	bsq->grid = lines;
	if (lines[0])
		bsq->cols = ft_strlen(lines[0]);
	else
		bsq->cols = 0;
	return (true);
}