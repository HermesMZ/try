/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:46:25 by zoum              #+#    #+#             */
/*   Updated: 2025/10/09 12:01:44 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	count_commands(int argc, char **argv)
{
	int	i;
	int	count;

	i = 1;
	count = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0)
			count++;
		i++;
	}
	return (count);
}

t_cmd	**create_commands(int argc, char **argv)
{
	int		i;
	t_cmd	**cmds;
	int		cmd_count;

	cmd_count = count_commands(argc, argv);
	cmds = malloc(sizeof(t_cmd *) * (cmd_count + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		cmds[i] = malloc(sizeof(t_cmd));
		if (!cmds[i])
			return (NULL);
		cmds[i]->fd_in = 0;
		cmds[i]->fd_out = 1;
		cmds[i]->has_pipe = 0;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
	{
		i++;
	}
	return (i);
}

int	parse_command(char **argv, t_cmd *cmd)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = count_args(argv);
	
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (-1);
	
	i = 0;
	while (i < arg_count)
	{
		cmd->args[i] = argv[i];
		i++;
	}
	cmd->args[i] = NULL;  // Terminer le tableau par NULL
	return (i);
}

t_cmd	**parse_commands(int argc, char **argv)
{
	t_cmd	**cmds;
	int		i;
	int		cmd_index;

	cmds = create_commands(argc, argv);
	if (!cmds)
		return (NULL);
	cmd_index = 0;
	i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			cmds[cmd_index]->has_pipe = 1;
			cmd_index++;
			i++;
		}
		else if (strcmp(argv[i], ";") == 0)
		{
			cmd_index++;
			i++;
		}
		else
		{
			i += parse_command(&argv[i], cmds[cmd_index]);
		}
	}
	return (cmds);
}

void	print_commands(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("Command %d:\n", i);
		int j = 0;
		while (cmds[i]->args[j])
		{
			printf("  arg[%d]: %s\n", j, cmds[i]->args[j]);
			j++;
		}
		printf("  has_pipe: %d\n", cmds[i]->has_pipe);
		printf("  fd_in: %d\n", cmds[i]->fd_in);
		printf("  fd_out: %d\n", cmds[i]->fd_out);
		i++;
	}
}

int	builtin_cd(t_cmd *cmd)
{
	if (!cmd->args[1] || cmd->args[2])
	{
		printf("mauvais arguments\n");
		return 1;
	}
	if (chdir(cmd->args[1]) != 0)
	{
		printf("'a marche po\n");
		return 1;
	}
	return 0;
}

void	exec_in_child(t_cmd *cmd, char **envp)
{
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, 1) < 0)
			return ;
		close(cmd->fd_out);
	}
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, 0) < 0)
			return ;
		close(cmd->fd_in);
	}
	if (execve(cmd->args[0], cmd->args, envp) < 0)
	{
		printf("chat marche poche\n");
	}
}

void	setup_pipe_if_needed(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->has_pipe)
	{
		if (pipe(pipe_fd) < 0)
			exit(1); // Error handling à améliorer
		cmd->fd_out = pipe_fd[1];
	}
	else
	{
		cmd->fd_out = 1;
	}
}

void	handle_parent_cleanup(t_cmd *cmd, int pipe_fd[2], int *prev_fd_in)
{
	// Fermer les file descriptors du parent
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	
	// Préparer pour la prochaine commande
	if (cmd->has_pipe)
		*prev_fd_in = pipe_fd[0];
	else
		*prev_fd_in = 0;
}

pid_t	execute_command(t_cmd *cmd, char **envp, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	
	if (pid == 0)
	{
		// Processus enfant
		if (cmd->has_pipe)
			close(pipe_fd[0]); // Fermer le read-end dans l'enfant
		exec_in_child(cmd, envp);
		
		exit(0);
	}
	
	return (pid);
}

int	exec(t_cmd **cmds, char **envp)
{
	int		i;
	int		pipe_fd[2];
	int		status;
	int		prev_fd_in;
	pid_t	pid;

	i = 0;
	prev_fd_in = 0;
	
	while (cmds[i])
	{
		if (strcmp(cmds[i]->args[0], "cd") == 0)
		{
			builtin_cd(cmds[i]);
			// cd ne génère pas de processus enfant, on passe à la commande suivante
		}
		else
		{
			// Configurer l'entrée de la commande
			cmds[i]->fd_in = prev_fd_in;
			
			// Configurer la sortie (pipe ou stdout)
			setup_pipe_if_needed(cmds[i], pipe_fd);
			
			// Exécuter la commande
			pid = execute_command(cmds[i], envp, pipe_fd);
			if (pid == -1)
				return (-1);
			
			// Nettoyer côté parent
			handle_parent_cleanup(cmds[i], pipe_fd, &prev_fd_in);
			
			// Attendre la fin si pas de pipe (exécution séquentielle)
			if (!cmds[i]->has_pipe)
				waitpid(pid, &status, 0);
		}
		
		// Nettoyer côté parent
		handle_parent_cleanup(cmds[i], pipe_fd, &prev_fd_in);
		
		// Attendre la fin si pas de pipe (exécution séquentielle)
		if (!cmds[i]->has_pipe)
			waitpid(pid, &status, 0);
		
		i++;
	}
	
	// Attendre tous les enfants restants (cas des pipes)
	while (waitpid(-1, &status, 0) > 0)
		;
	
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	**cmds;

	if (argc < 2)
		return (0);
	cmds = parse_commands(argc, argv);
	if (!cmds)
		return (1);
	exec(cmds, envp);
		
	int k = 0;
	while (cmds[k])
	{
		free(cmds[k]->args);
		free(cmds[k]);
		k++;
	}
	free(cmds);
	return (1);
}
