/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:51:23 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 11:27:09 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_file_error(t_data *data, int infile, int error)
{
	ft_putstr_fd(data->prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (infile)
		ft_putstr_fd(data->av[1], 2);
	else
		ft_putstr_fd(data->av[data->ac -1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error), 2);
}

void	ft_cmd_error(t_data *data, char *cmd, int error)
{
	ft_putstr_fd(cmd, 2);
	if (error == 127)
	{
		ft_putendl_fd(": command not found", 2);
		free(data->cmd);
		ft_free_tab(data->arg_cmd);
		ft_free_tab(data->env_path);
		exit (127);
	}
	else if (error == 126)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(data->cmd);
		ft_free_tab(data->arg_cmd);
		ft_free_tab(data->env_path);
		exit (126);
	}
}
