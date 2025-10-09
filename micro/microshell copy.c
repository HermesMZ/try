/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:09:19 by mzimeris          #+#    #+#             */
/*   Updated: 2025/10/08 21:33:24 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	print_commands(t_cmd **commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		printf("Command %d:\n", i);
		j = 0;
		while (commands[i]->args[j])
		{
			printf("  Arg[%d]: %s\n", j, commands[i]->args[j]);
			j++;
		}
		printf("  In: %d, Out: %d, Has pipe: %d\n", commands[i]->in, commands[i]->out, commands[i]->has_pipe);
		i++;
	}
}

int	count_commands(int argc, char **argv)
{
	int	count;

	count = 1;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '|' || argv[i][0] == ';')
			count++;
	}
	return (count);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] && args[count][0] != '|' && args[count][0] != ';')
		count++;
	return (count);
}

int	parse_commands(int argc, char **argv, t_cmd **commands, int cmd_count)
{
	int	i;
	int	cmd_index;
	int	arg_count;
	t_cmd	*cmd;

	cmd_index = 0;
	i = 1;
	while (i < argc)
	{
		arg_count = count_args(&argv[i]);
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
		{
			perror("malloc");
			return (1);
		}
		cmd->args = malloc(sizeof(char *) * (arg_count + 1));
		if (!cmd->args)
		{
			perror("malloc");
			free(cmd);
			return (1);
		}
		for (int j = 0; j < arg_count; j++)
		{
			cmd->args[j] = argv[i + j];
		}
		cmd->args[arg_count] = NULL;
		cmd->in = 0;
		cmd->out = 1;
		if (i + arg_count < argc && argv[i + arg_count][0] == '|')
			cmd->has_pipe = 1;
		else
			cmd->has_pipe = 0;
		commands[cmd_index++] = cmd;
		i += arg_count;
		if (i < argc && (argv[i][0] == '|' || argv[i][0] == ';'))
			i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cmd	**commands;
	int		cmd_count;

	printf("microshell\n");
	if (argc < 2)
	{
		printf("No commands provided.\n");
		return (0);
	}
	for (int i = 1; i < argc; i++)
		printf("Argument[%d]: %s\n", i, argv[i]);
	cmd_count = count_commands(argc, argv);
	commands = malloc(sizeof(t_cmd *) * (cmd_count + 1));
	if (!commands)
	{
		perror("malloc");
		return (1);
	}
	commands[cmd_count] = NULL;
	parse_commands(argc, argv, commands, cmd_count);
	print_commands(commands);
	printf("End of microshell\n");
	return (0);
}
