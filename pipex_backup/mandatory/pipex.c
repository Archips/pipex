/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/21 17:42:12 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_data *data, int status)
{
	if (pipe(data->fd) == -1)
		ft_exit(data, errno, -1);
	data->child[0] = fork();
	if (data->child[0] == -1)
		ft_exit(data, errno, -1);
	if (data->child[0] == 0)
		ft_child1(data);
	data->child[1] = fork();
	if (data->child[1] == -1)
		ft_exit(data, errno, -1);
	if (data->child[1] == 0)
		ft_child2(data);
	if (close(data->fd[0]) == 1)
		ft_exit(data, errno, 0);
	if (close(data->fd[1]) == 1)
		ft_exit(data, errno, 0);
	if (waitpid(data->child[0], NULL, 0) == -1)
		ft_exit(data, errno, 1);
	if (waitpid(data->child[1], &status, 0) == -1)
		ft_exit(data, errno, 1);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	data.prog_name = ft_strrchr(argv[0], '/') + 1;
	status = 1;
	if (argc == 5)
	{
		status = 0;
		if (!envp)
			exit(EXIT_FAILURE);
		ft_init_data(argc, argv, envp, &data);
		status = ft_pipex(&data, status);
		ft_free_all(&data);
		exit(status);
	}
	ft_putstr_fd(data.prog_name, 2);
	ft_putendl_fd(": Error: Arguments missing", 2);
	exit(status);
}
