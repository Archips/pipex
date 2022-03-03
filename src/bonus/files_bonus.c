/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:59:42 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 15:32:44 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open(t_data *data)
{
	if (data->here_doc && data->ac >= 6)
	{
		ft_here_doc(data);
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	}
	else
	{
		data->file_in = open(data->av[1], O_RDONLY);
		if (data->file_in == -1)
			ft_file_error(data, 1, errno);
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	if (data->file_out == -1)
	{
		ft_file_error(data, 0, errno);
		close(data->file_in);
		close(0);
		close(1);
		close(2);
		exit(EXIT_FAILURE);
	}
}
