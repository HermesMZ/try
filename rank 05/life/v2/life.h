/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:01:35 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/19 16:28:44 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_life
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	iteration;
	char			**grid;
}	t_life;

#endif