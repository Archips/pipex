/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:57:43 by athirion          #+#    #+#             */
/*   Updated: 2022/02/15 17:08:29 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_data *data)
{
	if (close(data->fd[0]) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data->file_in, STDIN_FILENO) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		perror("./pipex: dup2 - child1 - 2");
		exit(EXIT_FAILURE);
	}
	if (close(data->fd[1]) == -1 || close(data->file_in) == -1)
		exit(EXIT_FAILURE);
	data->arg_cmd[0] = ft_arg_cmd(data->av[2]);
	data->cmd[0] = ft_command(data->arg_cmd[0][0], data->env_path);
	if (execve(data->cmd[0], data->arg_cmd[0], data->env) == -1)
	{	
		ft_putstr_fd("./pipex: execve: command not found: ", 2);
		ft_putendl_fd(data->arg_cmd[0][0], 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_child2(t_data *data)
{
	if (close(data->fd[1]) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		perror("./pipex: dup2 - child2");
		exit(EXIT_FAILURE);
	}
	if (dup2(data->file_out, STDOUT_FILENO) == -1)
	{
		perror("./pipex: dup2 - child2 - 2");
		exit(EXIT_FAILURE);
	}
	if (close(data->fd[0]) == -1 || close(data->file_out) == -1)
		exit(EXIT_FAILURE);
	data->arg_cmd[1] = ft_arg_cmd(data->av[3]);
	data->cmd[1] = ft_command(data->arg_cmd[1][0], data->env_path);
	if (execve(data->cmd[1], data->arg_cmd[1], data->env) == -1)
	{
		ft_putstr_fd("./pipex: execve : command not found: ", 2);
		ft_putendl_fd(data->arg_cmd[1][0], 2);
		exit(127);
	}
}

