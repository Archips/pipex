/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/24 23:06:36 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_pipex(t_data *data, int status)
{
	int	i;
	int	child;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->fd) == -1)
			ft_exit(data, errno, -1);
		child = fork();
		if (child == -1)
			ft_exit(data, errno, -1);
		if (child > 0)
		{
			if (close(data->fd[1]) == -1)
				ft_exit(data, errno, -1);
			if (i != 0)
				if (dup2(data->fd[0], STDIN_FILENO) == -1)
					ft_exit(data, errno, -1);
			if (close(data->fd[0]) == -1)
				ft_exit(data, errno, -1);
			if (waitpid(child, &status, 0) == -1)
				ft_exit(data, errno, -1);
		}
		if (child == 0)
			ft_child(data, i);
		i ++;
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

void ft_child(t_data *data, int i)
{
	if (close(data->fd[0]) == -1)
		ft_exit(data, errno, -1);
	if (i == data->nb_cmd - 1)
	{
		if (dup2(data->file_out, STDOUT_FILENO) == -1)
			ft_exit(data, errno, -1);
	}
	else
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_exit(data, errno, -1);
	}
	if (close(data->fd[1]) == -1)
		ft_exit(data, errno, -1);
	if (!data->cmd[i])
		ft_exit(data, 127, i);
	if (execve(data->cmd[i], data->arg_cmd[i], data->env))
		ft_exit(data, 127, i);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	data.prog_name = ft_strrchr(argv[0], '/') + 1;
	status = 1;
	if (argc >= 5)
	{
		status = 0;
		if (!envp)
			exit(EXIT_FAILURE);
		printf("++++++++++++++++++++++++++\n");
		ft_init_data(argc, argv, envp, &data);
		if (dup2(data.file_in, STDIN_FILENO) == -1)
			ft_exit(&data, errno, -1);
		printf("++++++++++++++++++++++++++\n");
		status = ft_pipex(&data, status);
		if (close(data.file_in) == 1)
			ft_exit(&data, errno, 0);
		if (close(data.file_out) == 1)
			ft_exit(&data, errno, 0);
		//ft_free_all(&data);
		exit(status);
	}
	ft_putstr_fd(data.prog_name, 2);
	ft_putendl_fd(": Error: Arguments missing", 2);
	exit(status);
}
