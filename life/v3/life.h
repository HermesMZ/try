/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:53:14 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/29 17:33:40 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_life {
	int		width;
	int		height;
	int		iteration;
	char	**grid;
}	t_life;

#endif /*LIFE_H*/