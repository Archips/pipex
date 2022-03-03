/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:59:42 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 21:01:22 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open(t_data *data)
{
	data->file_in = open(data->av[1], O_RDONLY);
	if (data->file_in == -1)
		ft_file_error(data, 1, errno);
	data->file_out = open
		(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->file_out == -1)
	{
		ft_file_error(data, 0, errno);
		ft_close(data, &data->file_in);
		ft_close_std();
		exit(EXIT_FAILURE);
	}
}

void	ft_close(t_data *data, int *fd)
{
	if (*fd != -1)
		if (close(*fd) == -1)
			ft_exit(data, errno, NULL);
	*fd = -1;
}

void	ft_close_fd(t_data *data)
{
	if (data->fd[0] != -1)
		ft_close(data, &data->fd[0]);
	if (data->fd[1] != -1)
		ft_close(data, &data->fd[1]);
}

void	ft_close_std(void)
{
	close(0);
	close(1);
	close(2);
}

void	ft_close_all(t_data *data)
{
	ft_close(data, &data->file_in);
	ft_close(data, &data->file_out);
	ft_close(data, &data->fd[0]);
	ft_close(data, &data->fd[1]);
	close(0);
	close(1);
	close(2);
}
