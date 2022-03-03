/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:14:52 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 21:01:42 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_data *data, int status)
{
	int		i;
	int		child;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->fd) == -1)
			ft_exit(data, errno, NULL);
		child = fork();
		if (child == -1)
			ft_exit(data, errno, NULL);
		if (child > 0)
			status = ft_parent(data, i, status, child);
		if (child == 0)
			ft_child(data, i);
		ft_close_fd(data);
		i ++;
		data->index ++;
	}
	ft_close_fd(data);
	while (i--)
		wait(NULL);
	return (status);
}

int	ft_parent(t_data *data, int i, int status, int child)
{
	ft_close(data, &data->fd[1]);
	ft_dup(data, data->fd[0], STDIN_FILENO);
	ft_close(data, &data->fd[0]);
	if (i == data->nb_cmd - 1)
		if (waitpid(child, &status, 0) == -1)
			ft_exit(data, errno, NULL);
	if (WIFEXITED(status) == EXIT_FAILURE)
		status = WEXITSTATUS(status);
	return (status);
}

void	ft_child(t_data *data, int i)
{
	if (data->file_in < 0 && i == 0)
	{
		ft_free_tab(data->env_path);
		ft_close_all(data);
		exit(EXIT_FAILURE);
	}
	ft_close(data, &data->fd[0]);
	if (i == data->nb_cmd - 1)
	{
		ft_close(data, &data->fd[1]);
		ft_dup(data, data->file_out, STDOUT_FILENO);
		ft_close(data, &data->file_out);
	}
	else
	{
		ft_dup(data, data->fd[1], STDOUT_FILENO);
		ft_close(data, &data->fd[1]);
	}
	data->arg_cmd = ft_arg_cmd(data->av[data->index]);
	data->cmd = ft_command(data->arg_cmd[0], data->env_path);
	if (!data->cmd)
		ft_exit(data, 127, data->arg_cmd[0]);
	if (execve(data->cmd, data->arg_cmd, data->env) == -1)
		ft_exit(data, 126, data->arg_cmd[0]);
}

void	ft_dup(t_data *data, int fd, int std)
{
	if (dup2(fd, std) == -1)
		ft_exit(data, errno, NULL);
}
