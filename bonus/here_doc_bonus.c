/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:16:05 by athirion          #+#    #+#             */
/*   Updated: 2022/02/18 22:25:48 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_is_heredoc(t_data *data)
{
	if (ft_strncmp(data->av[1], "here_doc", 8) == 0)
		data->here_doc = 1;
	else
		data->here_doc = 0;
}

void	ft_here_doc(t_data *data)
{
	char	*temp;
	int		fd_file;
	
	fd_file = open(".temp_here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_file == -1)
		ft_exit(data, errno, -1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		temp = get_next_line(0);
		if (!temp)
			ft_exit(data, errno, -1);
		if (!ft_strncmp(temp, LIMITER, ft_strlen(LIMITER)))
			break;
		write(1, temp, ft_strlen(temp);
		free(temp);
	}
	free(temp);
	if (close(fd_file) == -1)
		ft_exit(data, errno, -1);
	data->file_in = open(".temp_here_doc", O_RDONLY);
	if (data->file_in == -1)
	{
		unlink(".temp_here_doc");
		ft_exit(data, errno, -1);
	}
}
