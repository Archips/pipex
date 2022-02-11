/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:56:18 by athirion          #+#    #+#             */
/*   Updated: 2022/02/11 14:05:24 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **envp)
{
	char	*path;
	char	**env_path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_strdup(*envp + 5);
	if (!path)
		return (ft_error(1), NULL);
	env_path = ft_split(path, ':');
	if (!env_path)
		return (ft_error(1), NULL);
	free(path);
	return (env_path);
}

char	*ft_command(char *cmd, char **env_path)
{
	char	*command;
	char	*new_path;

	while (*env_path)
	{
		new_path = ft_strjoin(*env_path, "/");
		if (!new_path)
			return (ft_error(1), NULL);
		command = ft_strjoin(new_path, cmd);
		if (!command)
			return (ft_error(1), NULL);
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

char	**arg_cmd(char *cmd)
{
	char	**arg_cmd;

	arg_cmd = ft_split(cmd, ' ');
	if (!arg_cmd)
		return (ft_error(1), NULL);
	return (arg_cmd);
}
