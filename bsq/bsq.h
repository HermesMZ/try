/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:20:42 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/15 15:44:52 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_bsq
{
	unsigned int	lines;
	unsigned int	cols;
	unsigned char	empty;
	unsigned char	obstacle;
	unsigned char	full;
	char			**grid;
}	t_bsq;


#endif /* BSQ_H */