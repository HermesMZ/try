/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:09:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/08 20:09:24 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <wait.h>

typedef struct s_cmd
{
	char	**args;
	int		in;
	int		out;
	int		has_pipe;
}	t_cmd;

#endif