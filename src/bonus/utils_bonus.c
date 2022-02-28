/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:54:44 by athirion          #+#    #+#             */
/*   Updated: 2022/02/26 22:09:19 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->ac = argc;
	data->av = argv;
	data->env = envp;
	data->nb_cmd = data->ac - 3 - data->here_doc;
	ft_open(data);
	data->env_path = ft_get_path(data->env);
	data->index = 2 + data->here_doc;
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

void	ft_close(t_data *data, int fd)
{
	if (close(fd) == -1)
		ft_exit(data, errno, NULL);
}

void	ft_exit(t_data *data, int error, char *cmd)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (error == 127)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		ft_free_tab(data->env_path);
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
	ft_free_tab(data->env_path);
	exit(EXIT_FAILURE);
}
