/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:36:35 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/02 16:43:51 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <error.h>

typedef struct s_bsq
{
	unsigned int	lines;
	char			empty;
	char			obstacle;
	char			full;
	char			**grid;
	unsigned int	cols;
}	t_bsq;

#endif