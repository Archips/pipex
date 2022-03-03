/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:54:44 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 16:51:31 by athirion         ###   ########.fr       */
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
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}	

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_dup(t_data *data, int fd, int std)
{
	if (dup2(fd, std) == -1)
		ft_exit(data, errno, NULL);
}

void	ft_exit(t_data *data, int error, char *cmd)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (error == 127)
		ft_cmd_error(data, cmd, error);
	else if (error == 126)
		ft_cmd_error(data, cmd, error);
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
