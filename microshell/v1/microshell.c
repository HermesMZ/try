/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:58:01 by zoum              #+#    #+#             */
/*   Updated: 2025/10/13 17:17:46 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

#define BAD_ARGS "error: cd: bad arguments\n"
#define CD_FAIL "error: cd: cannot change directory to "
#define FATAL "error: fatal\n"
#define EXEC_FAIL "error: cannot execute "

int	exec_fail(char *arg)
{
	write(2, EXEC_FAIL, strlen(EXEC_FAIL));
	write(2, arg, strlen(arg));
	write(2, "\n", 2);
	exit(127);
}

int	find_next_pipe(char *argv[], int *i)
{
	while (argv[*i])
	{
		if (strcmp(argv[*i], "|") == 0)
		{
			argv[*i] = NULL;
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	clean_parent(int *in_fd, int *out_fd, int pipe_fd[2], int has_pipe)
{
	if (*out_fd != 1)
		close(*out_fd);
	if (*in_fd != 0)
		close(*in_fd);
	if (has_pipe)
	{
		*in_fd = pipe_fd[0];
		*out_fd = 1;
	}
	else
	{
		*in_fd = 0;
		*out_fd = 1;
	}
	return (0);
}

int	clean_child(int *in_fd, int *out_fd, int pipe_fd[2], int has_pipe)
{
	if (has_pipe)
		close(pipe_fd[0]);
	if (*out_fd != 1)
	{
		if (dup2(*out_fd, 1) < 0)
			return (write(2, FATAL, strlen(FATAL)), 1);
		close(*out_fd);
	}
	if (*in_fd != 0)
	{
		if (dup2(*in_fd, 0) < 0)
			return (write(2, FATAL, strlen(FATAL)), 1);
		close(*in_fd);
	}
	return (0);
}

int	exec(char *argv[], int *i, char *envp[])
{
	int	in_fd;
	int	out_fd;
	int	pipe_fd[2];
	int	pid;
	int	has_pipe;
	int start;

	out_fd = 1;
	in_fd = 0;
	while (argv[*i])
	{
		start = *i;
		has_pipe = find_next_pipe(argv, i);
		if (has_pipe)
		{
			if (pipe(pipe_fd) < 0)
				return (write(2, FATAL, strlen(FATAL)), 1);
			out_fd = pipe_fd[1];
		}
		pid = fork();
		if (pid < 0)
		{
			return (write(2, FATAL, strlen(FATAL)), 1);
		}
		if (pid == 0)
		{
			clean_child(&in_fd, &out_fd, pipe_fd, has_pipe);
			execve(argv[start], argv + start, envp);
			exec_fail(argv[start]);
			exit(127);
		}
		if (pid > 0)
			clean_parent(&in_fd, &out_fd, pipe_fd, has_pipe);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

int	builtin(char *argv[], int *i)
{
	if (!argv[*i + 1] || argv[*i + 2])
		write(2, BAD_ARGS, strlen(BAD_ARGS));
	else if (chdir(argv[*i + 1]) < 0)
	{
		write(2, CD_FAIL, strlen(CD_FAIL));
		write(2, argv[*i + 1], strlen(argv[*i + 1]));
		write(2, "\n", 2);
	}
	while (argv[*i])
		(*i)++;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i;

	if (argc < 2)
		return (1);
	i = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], ";") == 0)
			argv[i] = NULL;
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "cd") == 0)
			builtin(argv, &i);
		else
			exec(argv, &i, envp);
		i++;
	}
	return (0);
}

	// i = -1;
	// while (++i < argc)
	// 	printf("argv[%d] = %s\n", i, argv[i]);