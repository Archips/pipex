/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:16:05 by athirion          #+#    #+#             */
/*   Updated: 2022/02/21 14:07:36 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_is_heredoc(t_data *data)
{
	if (ft_strncmp(data->av[1], "here_doc", 8) == 0)
	{
		data->here_doc = 1;
		return (1);
	}
	data->here_doc = 0;
	return (0);
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
		write(1, "pipe heredoc> ", 14);
		temp = get_next_line(0);
		if (!temp)
			ft_exit(data, errno, -1);
		if (!ft_strncmp(temp, data->av[2], ft_strlen(LIMITER)))
			break ;
		write(fd_file, temp, ft_strlen(temp));
		free(temp);
	}
	free(temp);
	ft_close(data, fd_file);
	data->file_in = open(".temp_here_doc", O_RDONLY);
	unlink(".temp_here_doc");
	if (data->file_in == -1)
		ft_exit(data, errno, -1);
}
