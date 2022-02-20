/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:56:18 by athirion          #+#    #+#             */
/*   Updated: 2022/02/18 17:16:09 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	char	*path;
	char	**env_path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_strdup(*envp + 5);
	if (!path)
		return (NULL);
	env_path = ft_split(path, ':');
	free(path);
	if (!env_path)
		return (NULL);
	return (env_path);
}

char	*ft_command(char *cmd, char **env_path)
{
	char	*command;
	char	*new_path;

	if (access(cmd, 0) == 0)
	{
		command = ft_strdup(cmd);
		return (command);	
	}
	while (*env_path)
	{
		new_path = ft_strjoin(*env_path, "/");
		if (!new_path)
			return (NULL);
		command = ft_strjoin(new_path, cmd);
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

char	**ft_arg_cmd(char *cmd)
{
	char	**arg_cmd;

	arg_cmd = ft_split(cmd, ' ');
	if (!arg_cmd)
		return (NULL);
	return (arg_cmd);
}
