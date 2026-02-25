/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:17:06 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/09 18:20:33 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_life
{
	int		width;
	int		height;
	int		iterations;
	char	**grid;
	char	dead;
	char	live;
}	t_life;

#endif