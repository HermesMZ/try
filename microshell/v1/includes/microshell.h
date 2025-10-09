/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:55:29 by zoum              #+#    #+#             */
/*   Updated: 2025/09/23 16:30:21 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

#define CD_BAD_ARGS "error: cd: bad arguments\n"
#define CD_CANT_CHANGE "error: cd: cannot change directory to " // + path + "\n"
#define FATAL "error: fatal\n"
#define EXECVE_FAIL "error: cannot execute " // + cmd + "\n"

typedef struct s_cmd
{
	int		in;
	int		out;
	int		has_pipe;
	char	**args;
}	t_cmd;