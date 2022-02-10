#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

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

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char **env_path;
	char *command;

	env_path = ft_path(envp);
	command = ft_command("wc", env_path);

	char *arg[] = {"wc", "-l", "infile",  NULL};	
	execve(command, arg, envp);
	return (0);
}
