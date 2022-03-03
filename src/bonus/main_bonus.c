/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 20:25:19 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->ac = argc;
	data->av = argv;
	data->env = envp;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->file_in = -1;
	data->file_out = -1;
	data->nb_cmd = data->ac - 3 - data->here_doc;
	ft_open(data);
	data->env_path = ft_get_path(data->env);
	data->index = 2 + data->here_doc;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	data.prog_name = ft_strrchr(argv[0], '/') + 1;
	status = 1;
	if (argc >= 5 + ft_is_heredoc(&data, argv[1]))
	{
		status = 0;
		if (!envp)
			exit(EXIT_FAILURE);
		ft_init_data(argc, argv, envp, &data);
		if (data.file_in != -1)
			if (dup2(data.file_in, STDIN_FILENO) == -1)
				ft_exit(&data, ENOENT, data.av[1]);
		status = ft_pipex(&data, status);
		if (data.file_in != -1)
			ft_close(&data, &data.file_in);
		ft_close(&data, &data.file_out);
		ft_free_tab(data.env_path);
		ft_close_std();
		exit(status);
	}
	ft_putstr_fd(data.prog_name, 2);
	ft_putendl_fd(": Error: Arguments missing", 2);
	exit(status);
}
