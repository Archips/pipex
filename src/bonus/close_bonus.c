/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:37:05 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 16:53:56 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
