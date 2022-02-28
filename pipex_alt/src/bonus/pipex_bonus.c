/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/28 17:29:23 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_pipex(t_data *data, int status)
{
	int		i;
	int		child;

	i = 0;
	while (i < data->nb_cmd)
	{
		printf(">> %i\n", __LINE__);
		if (pipe(data->fd) == -1)
			ft_exit(data, errno, NULL);
		child = fork();
		printf("pipex>> %i\n", __LINE__);
		if (child == -1)
			ft_exit(data, errno, NULL);
		if (child == 0)
			ft_child(data, i);
		if (child > 0)
			status = ft_parent(data, i, status, child);
		i ++;
		data->index ++;
	}
	return (status);
}

int	ft_parent(t_data *data, int i, int status, int child)
{
	ft_close(data, data->fd[1]);
	if (i == 0)
	{
		ft_close(data, data->fd[0]);
		if (data->file_in != -1)
		{
			printf("ohiwehiowehiwe\n");
			if (dup2(data->file_in, STDIN_FILENO) == -1)
			{
				printf(">> %i\n", __LINE__);
				ft_exit(data, ENOENT, NULL);
				return (ENOENT);
			}
		}
		else
		{
			printf("Stop");
			return (1234);
		}
	}
	else
	{
		printf(">> %i\n", __LINE__);
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			ft_exit(data, errno, NULL);
		ft_close(data, data->fd[0]);
	}
	printf(">> %i\n", __LINE__);
	if (waitpid(child, &status, 0) == -1)
		ft_exit(data, errno, NULL);
	if (WIFEXITED(status) == EXIT_FAILURE)
		status = WEXITSTATUS(status);
	return (status);
}	

void	ft_child(t_data *data, int i)
{
	char	*cmd;
	char	**arg_cmd;

	ft_close(data, data->fd[0]);
	if (data->file_in == -1)
		ft_exit(data, errno, NULL);
	if (i == data->nb_cmd - 1)
	{
		printf(">> %i\n", __LINE__);
		if (dup2(data->file_out, STDOUT_FILENO) == -1)
			ft_exit(data, errno, NULL);
		printf(">> %i\n", __LINE__);
	}
	else
	{
		printf(">> %i\n", __LINE__);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_exit(data, errno, NULL);
	}
	printf(">> %i\n", __LINE__);
	ft_close(data, data->fd[1]);
	printf(">> %i\n", __LINE__);
	arg_cmd = ft_arg_cmd(data->av[data->index]);
	printf(">> %i\n", __LINE__);
	cmd = ft_command(arg_cmd[0], data->env_path);
	printf(">> %i\n", __LINE__);
	if (!cmd)
		ft_exit(data, 127, arg_cmd[0]);
	printf(">> %i\n", __LINE__);
	if (execve(cmd, arg_cmd, data->env) == -1)
		ft_exit(data, 126, arg_cmd[0]);
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
		printf(">> %i\n", __LINE__);
		if (!envp)
			exit(EXIT_FAILURE);
		printf(">> %i\n", __LINE__);
		ft_init_data(argc, argv, envp, &data);
		printf(">> %i\n", __LINE__);
		/* if (dup2(data.file_in, STDIN_FILENO) == -1) */
		/* 	ft_exit(&data, ENOENT, NULL); */
		printf(">> %i\n", __LINE__);
		status = ft_pipex(&data, status);
		printf(">> %i\n", __LINE__);
		if (data.file_in != -1)
			ft_close(&data, data.file_in);
		ft_close(&data, data.file_out);
		printf(">> %i\n", __LINE__);
		ft_free_tab(data.env_path);
		printf(">> %i\n", __LINE__);
		exit(status);
	}
	ft_putstr_fd(data.prog_name, 2);
	ft_putendl_fd(": Error: Arguments missing", 2);
	printf(">> %i\n", __LINE__);
	exit(status);
}
