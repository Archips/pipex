/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:16:05 by athirion          #+#    #+#             */
/*   Updated: 2022/03/01 18:43:51 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_is_heredoc(t_data *data, char *here_doc)
{
	if (here_doc)
	{
		if (ft_strncmp(here_doc, "here_doc", 8) == 0)
		{
			data->here_doc = 1;
			return (1);
		}
	}
	data->here_doc = 0;
	return (0);
}

void	ft_print_prompt(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		write(1, "pipe ", 5);
		i ++;
	}
	write(1, "heredoc> ", 9);
}

void	ft_here_doc(t_data *data)
{
	char	*temp;
	int		fd_file;

	fd_file = open(".temp_here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_file == -1)
		ft_exit(data, errno, NULL);
	while (1)
	{
		ft_print_prompt(data);
		temp = get_next_line(0);
		if (temp == NULL)
			ft_exit(data, errno, NULL);
		if (!ft_strncmp(temp, data->av[2], ft_strlen(data->av[2])))
			break ;
		write(fd_file, temp, ft_strlen(temp));
		free(temp);
	}
	free(temp);
	ft_close(data, fd_file);
	data->file_in = open(".temp_here_doc", O_RDONLY);
	unlink(".temp_here_doc");
}
