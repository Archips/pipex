/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:54:44 by athirion          #+#    #+#             */
/*   Updated: 2022/02/15 18:03:09 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_path(int argc, char **argv, char **envp, t_data *data)
{
	data->ac = argc;
	data->av = argv;
	data->env = envp;
	data->file_in = open(data->av[1], O_RDONLY);
	data->file_out = open(data->av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->file_out == -1)
		exit(errno);
	data->env_path = ft_get_path(data->env);
}

void	ft_free_tab(char **tab)
{
	char	**temp;

	temp = tab;

	while (*tab)
	{
		free(*tab);
		*tab = NULL;
		tab ++;
	}
	free(temp); 
	temp = NULL;
}

void	ft_exit(t_data *data, int error, int cmd_id)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (error == 127)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(data->arg_cmd[cmd_id][0], 2);
		exit(127);
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
		ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}
