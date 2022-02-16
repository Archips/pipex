/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:57:43 by athirion          #+#    #+#             */
/*   Updated: 2022/02/16 11:44:21 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_data *data)
{
	if (close(data->fd[0]) == -1)
		ft_exit(data, EXIT_FAILURE, -1);
	if (dup2(data->file_in, STDIN_FILENO) == -1)
		ft_exit(data, ENOENT, -1);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		ft_exit(data, EXIT_FAILURE, -1);
	if (close(data->fd[1]) == -1 || close(data->file_in) == -1)
		ft_exit(data, EXIT_FAILURE, -1);
	data->arg_cmd[0] = ft_arg_cmd(data->av[2]);
	data->cmd[0] = ft_command(data->arg_cmd[0][0], data->env_path);
	if (execve(data->cmd[0], data->arg_cmd[0], data->env) == -1)
	{
		ft_exit(data, 127, 0);
//		exit(127);
	}
}

void	ft_child2(t_data *data)
{
	if (close(data->fd[1]) == -1)
		ft_exit(data, EXIT_FAILURE, 0);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_exit(data, EXIT_FAILURE, 0);
	if (dup2(data->file_out, STDOUT_FILENO) == -1)
		ft_exit(data, EXIT_FAILURE, 0);
	if (close(data->fd[0]) == -1 || close(data->file_out) == -1)
		ft_exit(data, EXIT_FAILURE, 0);
	data->arg_cmd[1] = ft_arg_cmd(data->av[3]);
	data->cmd[1] = ft_command(data->arg_cmd[1][0], data->env_path);
	if (execve(data->cmd[1], data->arg_cmd[1], data->env) == -1)
	{
		ft_exit(data, 127, 1);
//		ft_free_all(data, 1);
//		exit(127);
	}
}

