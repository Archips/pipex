/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:54:44 by athirion          #+#    #+#             */
/*   Updated: 2022/02/24 22:43:00 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_data(int argc, char **argv, char **envp, t_data *data)
{
	int	index;
	int id;

	id = 0;
	data->ac = argc;
	printf("argc = [%d]\n", data->ac);
	data->av = argv;
	data->env = envp;
	ft_get_files_fd(data);
	printf("Infile fd = [%d]\n", data->file_in);
	printf("Outfile fd = [%d]\n", data->file_out);
	data->nb_cmd = data->ac - 3 - data->here_doc;
	printf("Nb_cmd = [%d]\n", data->nb_cmd);
	data->env_path = ft_get_path(data->env);
	printf("Here_doc = [%d]\n", data->here_doc);
	if (data->here_doc)
		index = 3;
	else
		index = 2;
	printf("Index = [%d]\n", index);
	while (id < data->nb_cmd)
	{
		data->arg_cmd[id] = ft_arg_cmd(data->av[index]);
		data->cmd[id] = ft_command(data->arg_cmd[id][0], data->env_path);
		printf("Cmd[%d] = [%s]\n", id, data->cmd[id]);
		index ++;
		id ++;
	}
	printf("======== INITIALISATION TERMINEE ========\n");
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i ++;
	}
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i ++;
	}
}

/* void	ft_init_pipe(t_data *data) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	data->pipe = (int **)malloc(sizeof(int) * (data->nb_cmd + 1)); */
/* 	if (!data->pipe) */
/* 		ft_exit(data, errno, -1); */
/* 	while (i < data->nb_cmd) */
/* 	{ */
/* 		data->pipe[i] = (int *)malloc(sizeof(int) * 2); */
/* 		if (!data->pipe[i]) */
/* 			ft_exit(data, errno, -1); */
/* 		if (pipe(data->pipe[i]) == -1) */
/* 			ft_exit(data, errno, -1); */
/* 		i ++; */
/* 	} */
/* } */


void	ft_open(t_data *data)
{
	if (!data->here_doc)
	{
		data->file_in = open(data->av[1], O_RDONLY);
		if (data->file_in == -1)
			ft_exit(data, errno, -1);
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (data->file_out == -1)
			ft_exit(data, errno, -1);
	}
	else
	{
		data->file_out = open
			(data->av[data->ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (data->file_out == -1)
			ft_exit(data, errno, -1);
	}
}

void	ft_close(t_data *data, int fd)
{
	if (close(fd) == -1)
		ft_exit(data, errno, -1);
}

void	ft_exit(t_data *data, int error, int cmd_id)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (error == 127)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(data->arg_cmd[cmd_id][0], 2);
//		ft_free_all(data);
		exit (127);
	}
	else if (error == ENOENT)
	{
		ft_putstr_fd(strerror(ENOENT), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(data->av[1], 2);
	}
	else if (errno)
	{
		ft_putstr_fd("error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		ft_putendl_fd("error: Something went wrong", 2);
//	ft_free_all(data);
	exit(EXIT_FAILURE);
}
