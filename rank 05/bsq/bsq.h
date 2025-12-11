/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:50:35 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/11 13:08:33 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_bsq
{
	unsigned int	lines;
	unsigned int	cols;
	unsigned char	empty;
	unsigned char	obstacle;
	unsigned char	full;
	char			**grid;
}	t_bsq;

bool	check_file(char *filename, t_bsq *bsq);
bool	check_stdin(t_bsq *bsq);
void	free_lines(char **lines);
void	print_bsq(t_bsq *bsq);
void	run_bsq(t_bsq *bsq, int max_square_size);
int		ft_strcpy(char *dest, const char *src);
int		ft_strlen(const char *str);
bool	parse_lines(FILE *file, t_bsq *bsq);
int	check_line(char *line, t_bsq *bsq, char **lines, int line_len);

#endif