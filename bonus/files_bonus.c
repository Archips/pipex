/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:59:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/21 17:52:35 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_get_infile_fd(t_data *data)
{
	if (ft_is_heredoc(data) && data->ac == 6)
		ft_here_doc(data);
	else
	{
		data->file_in = open(data->av[1], O_RDONLY);
		if (data->file_in == -1)
			ft_exit(data, errno, -1);
	}
}

void	ft_get_outfile_fd(t_data *data)
{
	if (data->here_doc == 1)
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->file_out == -1)
		ft_exit(data, errno, -1);
}

void	ft_get_filenames(t_data *data)
{
	ft_get_infile_fd(data);
	ft_get_outfile_fd(data);
}
