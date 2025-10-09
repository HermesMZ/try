/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:40:54 by zoum              #+#    #+#             */
/*   Updated: 2025/10/08 23:43:38 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_cmd
{
	char			**args;
	int				arg_count;
	int				has_pipe;
	int				fd_in;
	int				fd_out;
}	t_cmd;


#endif