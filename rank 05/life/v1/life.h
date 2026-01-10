/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:47:31 by zoum              #+#    #+#             */
/*   Updated: 2025/12/12 23:55:41 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_life
{
	int		width;
	int		height;
	int		iteration;
	char	**grid;
}			t_life;




#endif