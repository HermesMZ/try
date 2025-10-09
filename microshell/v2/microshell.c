/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:14:07 by zoum              #+#    #+#             */
/*   Updated: 2025/10/09 15:23:43 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

#define CD_BAD_ARGS "error: cd: bad arguments\n"
#define CD_CANT_CHANGE "error: cd: cannot change directory to "
#define FATAL "error: fatal\n"
#define EXECVE_FAIL "error: cannot execute "

void	fatal(void)
{
	write(2, FATAL, strlen(FATAL));
	exit(1);
}

void	exec_error(char *cmd)
{
	write(2, EXECVE_FAIL, strlen(EXECVE_FAIL));
	write(2, cmd, strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}

void	builtin_cd(char **argv, int *i)
{
	if (!argv[*i + 1] || argv[*i + 2])
	{
		write(2, CD_BAD_ARGS, strlen(CD_BAD_ARGS));
		*i += 1;
		return ;
	}
	if (chdir(argv[*i + 1]) != 0)
	{
		write(2, CD_CANT_CHANGE, strlen(CD_CANT_CHANGE));
		write(2, argv[*i + 1], strlen(argv[*i + 1]));
		write(2, "\n", 1);
	}
	*i += 2;
	// printf("pwd after cd: %s\n", getcwd(NULL, 0));
}

int	find_next_pipe(char **argv, int *i)
{
	while (argv[*i])
	{
		if (strcmp(argv[*i], "|") == 0)
		{
			argv[*i] = NULL;
			*i += 1; // début de la prochaine commande
			return (1); // pipe trouvé
		}
		*i += 1;
	}
	return (0);
}

void	exec_command_in_child(char **argv, int in_fd, int out_fd, char *envp[])
{
	if (in_fd != 0)
	{
		if (dup2(in_fd, 0) < 0)
			fatal();
		close(in_fd);
	}
	if (out_fd != 1)
	{
		if (dup2(out_fd, 1) < 0)
			fatal();
		close(out_fd);
	}
	execve(argv[0], argv, envp);
	exec_error(argv[0]);
}

void	execute_command(char **argv, int *i, char *envp[])
{
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	int		start;
	int		has_pipe;
	pid_t	pid;

	in_fd = 0;

	while (argv[*i] && argv[*i][0] != '\0')
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
		if (pid == 0) // enfant
		{
			if (in_fd != 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (out_fd != 1)
			{
				dup2(out_fd, 1);
				close(out_fd);
			}
			if (has_pipe)
				close(pipe_fd[0]);
			execve(argv[start], argv + start, envp);
			exec_error(argv[start]);
		}
		else // parent
		{
			if (in_fd != 0)
				close(in_fd);
			if (has_pipe)
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
			else
				in_fd = 0;
		}
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}

int main(int argc, char *argv[], char *envp[])
{
	int	i;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], ";") == 0)
			argv[i] = NULL;
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (!argv[i])
		{
			i++;
			continue ;
		}
		if (strcmp(argv[i], "cd") == 0)
			builtin_cd(argv, &i);
		else
			execute_command(argv, &i, envp);
	}
	return (0);
}

// explication du suivi de i:
// remplacement des ";" par NULL pour faciliter le traitement
// - i est l'index courant dans argv
// - pour "cd", on incrémente i de 2 (commande + argument)
// - pour une commande avec pipes, execute_command met à jour i pour pointer
//   après la dernière commande (après le NULL inséré) avec la fonction find_next_pipe
// - si on rencontre un NULL (anciennement ";"), on l'ignore et on passe au suivant
// - la boucle continue jusqu'à la fin des arguments (i < argc)
