/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:16:05 by athirion          #+#    #+#             */
/*   Updated: 2022/03/05 09:34:06 by athirion         ###   ########.fr       */
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

void	ft_end_heredoc(t_data *data)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": here-document delimited by end-of-line (wanted '", 2);
	ft_putstr_fd(data->av[2], 2);
	ft_putendl_fd("')", 2);
}

void	ft_here_doc(t_data *data)
{
	char	*temp;
	int		fd_file;

	fd_file = open("/tmp/temp_heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_file == -1)
		ft_exit(data, errno, NULL);
	while (1)
	{
		write(1, "> ", 2);
		temp = get_next_line(0);
		if (temp == NULL)
		{
			ft_end_heredoc(data);
			break ;
		}
		if (!ft_strncmp(temp, data->av[2], ft_strlen(data->av[2])))
			break ;
		write(fd_file, temp, ft_strlen(temp));
		free(temp);
	}
	free(temp);
	ft_close(data, &fd_file);
	data->file_in = open("/tmp/temp_heredoc", O_RDONLY);
	unlink("/tmp/temp_heredoc");
}
