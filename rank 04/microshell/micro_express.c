/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:54:28 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/09 15:03:43 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void	ft_msg(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	cd(char *av[], int i)
{
	if (i != 2)
		return (ft_msg("error: cd: bad arguments\n"), 1);
	if (chdir(av[1]) == -1)
		return (ft_msg("error: cd: cannot change directory to "),
			ft_msg(av[1]), ft_msg("\n"), 1);
	return (0);
}

void    set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		ft_msg("error: fatal\n"), exit(1);
}

int	exec(char *av[], int i, char *env[], int has_pipe)
{
	int	fd[2];
	int	status;
	int	pid;

	if (!has_pipe && !strcmp(*av, "cd"))
		return (cd(av, i));
	if ((has_pipe && pipe(fd) == -1) || (pid = fork()) == -1)
		ft_msg("error: fatal\n"), exit(1);
	if (pid == 0)
	{
		av[i] = 0;
		set_pipe(has_pipe, fd, 1);
		if (!strcmp(*av, "cd"))
			exit(cd(av, i));
		if (execve(*av, av, env) == -1)
			ft_msg("error: cannot execute "), ft_msg(av[0]), ft_msg("\n"), exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char *av[], char *env[])
{
	int	status = 0;
	int	i = 0;

	(void)ac;
	while (av[i])
	{
		av += i + 1;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (i)
			status = exec(av, i, env, av[i] && !strcmp(av[i], "|"));
	}
	return (status);
}
