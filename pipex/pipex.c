/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/10 21:25:30 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **ft_path(char **envp)
{
	char *path;
	char **env_path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_strdup(*envp + 5);
	env_path = ft_split(path, ':');
	return (env_path);
}

char *ft_command(char *cmd, char **env_path)
{
	char *command;
	char *new_path;

	while (*env_path)
	{
		new_path = ft_strjoin(*env_path, "/");
		if (!new_path)
			return (NULL);
		command = ft_strjoin(new_path, cmd);
		if (!command)
			return (NULL);
		if (access(command, 0) == 0)
		{
			free(new_path);
			return (command);
		}
		env_path ++;
		free(new_path);
		free(command);
	}
	return (NULL);
}

char **arg_cmd(char *cmd)
{
	char **arg_cmd;

	arg_cmd = ft_split(cmd, ' ');
	int i;

	i = 0;
	while (arg_cmd[i])
	{
		printf("Arg_cmd[%d] = %s\n", i, arg_cmd[i]);
		i++;
	}
	return (arg_cmd);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;

	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	char	**env_path;
	char	*cmd1;
	char	*cmd2;
	int		f_in;
	int		f_out;

	f_in = open(argv[1], O_RDONLY);
	f_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);

	if (pipe(fd) == -1)
		return (1);
	child1 = fork();
	if (child1 < 0)
		return (0);
	env_path = ft_path(envp);
	if (child1 == 0)
	{	
		printf("Hello child 1\n");
		return (0);
		printf("Hello child 1\n");
		char **arg_cmd1 = arg_cmd(argv[2]);
		cmd1 = ft_command(arg_cmd1[0], env_path);
		dup2(f_in, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmd1, arg_cmd1, envp);
	}
	child2 = fork();
	if (child2 < 0)
		return (3);
	if (child2 == 0)
	{
		printf("Hello child 2\n");
		char **arg_cmd2 = arg_cmd(argv[3]);
		cmd2 = ft_command(arg_cmd2[0], env_path);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		dup2(f_out, STDOUT_FILENO);
		execve(cmd2, arg_cmd2, envp);
	}
	close(fd[1]);
	close(fd[0]);

	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	system("leaks pipex");
	return (0);
}
