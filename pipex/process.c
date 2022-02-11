/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:57:43 by athirion          #+#    #+#             */
/*   Updated: 2022/02/11 14:08:09 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_data *data, char **argv, char **envp)
{
	data->arg_cmd1 = arg_cmd(argv[2]);
	data->cmd1 = ft_command(data->arg_cmd1[0], data->env_path);
	if (dup2(data->fd_in, STDIN_FILENO) == -1)
	{
		perror("./pipex");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("./pipex");
		exit(EXIT_FAILURE);
	}
	close(data->fd[0]);
	if (execve(data->cmd1, data->arg_cmd1, envp) == -1)
	{	
		perror("./pipex");
		exit(EXIT_FAILURE);
	}
}

void	ft_child2(t_data *data, char **argv, char **envp)
{
	data->arg_cmd1 = arg_cmd(argv[3]);
	data->cmd1 = ft_command(data->arg_cmd1[0], data->env_path);
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		perror("./pipex");
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		perror("./pipex");
	close(data->fd[1]);
	if (execve(data->cmd1, data->arg_cmd1, envp) == -1)
		perror("./pipex");
}
