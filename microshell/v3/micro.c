/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:27:48 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/09 15:21:46 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>

int	builtin(char **argv, int *i)
{
	printf("argv[%d] = %s\n", *i, argv[*i]);
	if (!argv[*i + 1])
		return (write(2, "need\n", 5), 1);
	if (argv[*i + 2])
		return (write(2, "much\n", 5), 1);
	if (chdir(argv[*i + 1]) < 0)
		return (write(2, "fail\n", 5), 1);
	*i += 2;
	return (0);
}

int	find_pipe(char **argv, int *i)
{
	while (argv[*i])
	{
		if (strcmp(argv[*i], "|") == 0)
		{
			argv[*i] = NULL;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

void	clean_parent_fds(int pipe_fd[2], int *in_fd, int has_pipe)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (has_pipe)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
	else
		*in_fd = 0;
}

void    set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
	{
		printf("error: fatal\n");
		exit(1);
	}
}


int	exec(char **argv, char **envp, int *i)
{
	pid_t	pid;
	int		start;
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	int		has_pipe;

	in_fd = 0;
	while (argv[*i])
	{
		start = *i;
		has_pipe = find_pipe(argv, i);
		set_pipe(has_pipe, pipe_fd, 1);
		if (has_pipe)
		{
			if (pipe(pipe_fd) < 0)
				return (write(2, "pipe\n", 5), 1);
			out_fd = pipe_fd[1];
		}
		else
			out_fd = 1;
		pid = fork();
		if (pid < 0)
			return (write(2, "fork\n", 5), 1);
		if (pid == 0)
		{
			if (in_fd != 0)
			{
				if (dup2(in_fd, 0) < 0)
					return (write(2, "dup2\n", 5), 1);
				close(in_fd);
			}
			if (out_fd != 0)
			{
				if (dup2(out_fd, 1) < 0)
					return (write(2, "dup2\n", 5), 1);
				close(out_fd);
			}
			if (has_pipe)
				close(pipe_fd[0]);
			execve(argv[start], argv + start, envp);
		}
		else
			set_pipe(has_pipe, pipe_fd, 0);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	int i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], ";") == 0)
			argv[i] = NULL;
		i++;
	}
	i = 1;
	while (i < argc)
	{
	printf("%s\n", argv[i]);


		if (strcmp(argv[i], "cd") == 0)
			builtin(argv, &i);
		else
			exec(&argv[i], envp, &i);
		while (!argv[i])
			i++;
	}
	return (0);
}
