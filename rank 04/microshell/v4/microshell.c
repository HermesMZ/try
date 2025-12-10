/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:30:24 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/29 15:54:46 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

#define CD_BAD_ARGS "error: cd: bad arguments\n"
#define CD_CANT_CHANGE "error: cd: cannot change directory to "
#define FATAL "error: fatal\n"
#define EXECVE_FAIL "error: cannot execute "

void	fatal(void)
{
	write(2, FATAL, strlen(FATAL));
	exit(1);
}

void	exec_fail(char *cmd)
{
	write(2, EXECVE_FAIL, strlen(EXECVE_FAIL));
	write(2, cmd, strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}

int	builtin(char *argv[], int *i)
{
	if (!argv[*i + 1] || argv[*i + 2])
		return (write(2, CD_BAD_ARGS, strlen(CD_BAD_ARGS)), 1);
	if (chdir(argv[*i + 1]) < 0)
	{
		write(2, CD_CANT_CHANGE, strlen(CD_CANT_CHANGE));
		write(2, argv[*i + 1], strlen(argv[*i + 1]));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
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

void	clean_child_fd(int out_fd, int in_fd, int pipe_fd[2], int has_pipe)
{
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (has_pipe)
		close(pipe_fd[0]);
}

void	clean_parent_fd(int *in_fd, int pipe_fd[2], int has_pipe)
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

int	exec(char *argv[], int *i, char *envp[])
{
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	pid_t	pid;
	int		has_pipe;
	int		start;

	in_fd = 0;
	out_fd = 1;
	while (argv[*i])
	{
		start = *i;
		has_pipe = find_next_pipe(argv, i);
		if (has_pipe)
		{
			if (pipe(pipe_fd) < 0)
				fatal();
			out_fd = pipe_fd[1];
		}
		else
			out_fd = 1;
		pid = fork();
		if (pid < 0)
			fatal();
		if (pid == 0)
		{
			clean_child_fd(out_fd, in_fd, pipe_fd, has_pipe);
			execve(argv[start], argv + start, envp);
			exec_fail(argv[start]);
		}
		if (pid > 0)
			clean_parent_fd(&in_fd, pipe_fd, has_pipe);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i;

	if (argc < 2)
		return (1);
	i = 0;
	while (i < argc && argv[i])
	{
		if (strcmp(argv[i], ";") == 0)
			argv[i] = NULL;
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "cd") == 0)
		{
			builtin(argv, &i);
			while (argv[i])
				i++;
		}
		else
			exec(argv, &i, envp);
		i++;
	}
	return (0);
}
