/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:57:43 by athirion          #+#    #+#             */
/*   Updated: 2022/02/11 17:25:05 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_data *data, char **argv, char **envp)
{
	data->arg_cmd1 = arg_cmd(argv[2]);
	data->cmd1 = ft_command(data->arg_cmd1[0], data->env_path);
	if (dup2(data->fd_in, STDIN_FILENO) == -1)
	{
		perror("./pipex : dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("./pipex : dup2");
		exit(EXIT_FAILURE);
	}
	close(data->fd[0]);
	if (execve(data->cmd1, data->arg_cmd1, envp) == -1)
	{	
		perror("./pipex : execve");
		exit(EXIT_FAILURE);
	}
}

void	ft_child2(t_data *data, char **argv, char **envp)
{
	data->arg_cmd2 = arg_cmd(argv[3]);
	data->cmd2 = ft_command(data->arg_cmd2[0], data->env_path);
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		perror("./pipex : dup2");
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		perror("./pipex : dup2");
	close(data->fd[1]);
	if (execve(data->cmd2, data->arg_cmd2, envp) == -1)
		perror("./pipex : execve");
}
