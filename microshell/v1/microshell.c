/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:08:40 by zoum              #+#    #+#             */
/*   Updated: 2025/09/23 18:08:43 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/microshell.h"

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

void	free_commands(t_cmd **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i]->args[j])
			free(cmds[i]->args[j++]);
		free(cmds[i]->args);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_cmd	*add_command(t_cmd *cmd, int *j, char **argv, int arg_count)
{
	int	i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->in = 0;
	cmd->out = 1;
	cmd->has_pipe = 0;
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < arg_count)
	{
		cmd->args[i] = ft_strdup(argv[*j]);
		if (!cmd->args[i])
		{
			while (i >= 0)
				free(cmd->args[i--]);
			free(cmd);
			return (NULL);
		}
		(*j)++;
		i++;
	}
	cmd->args[i] = NULL;
	if (argv[*j] && strcmp(argv[*j], "|") == 0)
	{
		cmd->has_pipe = 1;
		(*j)++;
	}
	if (argv[*j] && strcmp(argv[*j], ";") == 0)
		(*j)++;
	return (cmd);
}

int	count_commands(int argc, char *argv[])
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "|") == 0)
			count++;
		if (strcmp(argv[i], ";") == 0)
			count++;
		i++;
	}
	return (count);
}

int	count_args(int start, char *argv[])
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

t_cmd	**parse_commands(int argc, char *argv[])
{
	t_cmd	**cmds;
	int		command_count;
	int		arg_count;
	int		i;
	int		j;

	command_count = count_commands(argc, argv);
	cmds = malloc(sizeof(t_cmd *) * (command_count + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	j = 1;
	while (i < command_count)
	{
		arg_count = count_args(j, argv);
		cmds[i] = add_command(cmds[i], &j, argv, arg_count);
		if (!cmds[i])
		{
			while (i >= 0)
				free(cmds[i--]);
			free(cmds);
			return (NULL);
		}
		i++;

	}
	cmds[i] = NULL;
	return (cmds);
}

void	 print_commands(t_cmd **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		printf("Command %d:\n", i);
		printf("  in: %d\n", cmds[i]->in);
		printf("  out: %d\n", cmds[i]->out);
		printf("  has_pipe: %d\n", cmds[i]->has_pipe);
		j = 0;
		while (cmds[i]->args[j])
		{
			printf("  args[%d]: %s\n", j, cmds[i]->args[j]);
			j++;
		}
		i++;
	}
}

void	builtin_cd(t_cmd *cmd)
{
	if (!cmd->args[1] || cmd->args[2])
	{
		write(2, CD_BAD_ARGS, strlen(CD_BAD_ARGS));
		return ;
	}
	if (chdir(cmd->args[1]) != 0)
	{
		write(2, CD_CANT_CHANGE, strlen(CD_CANT_CHANGE));
		write(2, cmd->args[1], strlen(cmd->args[1]));
		write(2, "\n", 1);
	}
	// printf("pwd after cd: %s\n", getcwd(NULL, 0));
}

void	exec_cmd_in_child(t_cmd *cmd, char *envp[])
{
	if (cmd->in != 0)
	{
		if (dup2(cmd->in, 0) < 0)
			fatal();
		close(cmd->in);
	}
	if (cmd->out != 1)
	{
		if (dup2(cmd->out, 1) < 0)
			fatal();
		close(cmd->out);
	}
	if (execve(cmd->args[0], cmd->args, envp) < 0)
		exec_error(cmd->args[0]);
}

void	execute_commands(t_cmd **cmd, char *envp[])
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->has_pipe)
		{
			if (pipe(pipe_fd) < 0)
				fatal();
			cmd[i]->out = pipe_fd[1];
			cmd[i + 1]->in = pipe_fd[0];
		}
		pid = fork();
		if (pid < 0)
		{
			if (cmd[i]->has_pipe)
				fatal();
		}
		if (pid == 0)
		{
			if (cmd[i]->has_pipe)
				close(pipe_fd[0]);
			exec_cmd_in_child(cmd[i], envp);
		}
		else
		{
			if (cmd[i]->out != 1)
				close(pipe_fd[1]);
			if (cmd[i]->in != 0)
				close(pipe_fd[0]);
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	**cmds;

	if (argc < 2)
		return (0);
	cmds = parse_commands(argc, argv);
	if (!cmds)
		fatal();
	print_commands(cmds);
	if (strcmp(cmds[0]->args[0], "cd") == 0)
		builtin_cd(cmds[0]);
	else
		execute_commands(cmds, envp);
	free_commands(cmds);
	return (0);
}
