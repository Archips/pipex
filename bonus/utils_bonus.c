/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:54:44 by athirion          #+#    #+#             */
/*   Updated: 2022/02/21 14:01:16 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_data(int argc, char **argv, char **envp, t_data *data)
{
	int	index;
	int	id;

	id = 0;
	data->ac = argc;
	data->av = argv;
	data->env = envp;
	ft_get_filenames(data);
	data->nb_cmd = data->ac - 3;
//	data->pipe = (pid_t *)malloc(sizeof(pid_t) * (data->nb_cmd + 1));
	if (!data->pipe)
		ft_exit(data, errno, -1);
	data->env_path = ft_get_path(data->env);
	index = data->ac - 3;
	while (index < data->ac - 1)
	{
		data->arg_cmd[id] = ft_arg_cmd(data->av[index]);
		data->cmd[id] = ft_command(data->arg_cmd[id][0], data->env_path);
		index ++;
		id ++;
	}
	data->cmd_id = id;
}

void	ft_open(t_data *data)
{
	if (!data->here_doc)
	{
		data->file_in = open(data->av[1], O_RDONLY);
		if (data->file_in == -1)
			ft_exit(data, errno, -1);
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (data->file_out == -1)
			ft_exit(data, errno, -1);
	}
	else
	{
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (data->file_out == -1)
			ft_exit(data, errno, -1);
	}
}

void	ft_close(t_data *data, int fd)
{
	if (close(fd) == -1)
		ft_exit(data, errno, -1);
}

void	ft_exit(t_data *data, int error, int cmd_id)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (error == 127)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(data->arg_cmd[cmd_id][0], 2);
		ft_free_all(data);
		exit (127);
	}
	else if (error == ENOENT)
	{
		ft_putstr_fd(strerror(ENOENT), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(data->av[1], 2);
	}
	else if (errno)
	{
		ft_putstr_fd("error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		ft_putendl_fd("error: Something went wrong", 2);
	ft_free_all(data);
	exit(EXIT_FAILURE);
}
