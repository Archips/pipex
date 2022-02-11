/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/11 14:21:36 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	ft_open(argv, &data);
	if (pipe(data.fd) == -1)
		perror("./pipex: ");
	data.env_path = ft_path(envp);
	data.child1 = fork();
	if (data.child1 < 0)
		perror("./pipex: ");
	if (data.child1 == 0)
		ft_child1(&data, argv, envp);
	data.child2 = fork();
	if (data.child2 < 0)
		perror("./pipex: ");
	if (data.child2 == 0)
		ft_child2(&data, argv, envp);
	close(data.fd[0]);
	close(data.fd[1]);
	ft_free_tab(data.env_path);
	waitpid(data.child1, NULL, 0);
	waitpid(data.child2, NULL, 0);
	return (0);
}
