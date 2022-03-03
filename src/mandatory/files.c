/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:59:42 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 11:30:25 by athirion         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
}
