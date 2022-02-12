/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:54:44 by athirion          #+#    #+#             */
/*   Updated: 2022/02/11 16:18:33 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open(char **argv, t_data *data)
{
	data->fd_in = open(argv[1], O_RDONLY);
	data->fd_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
}

int	ft_error(int error)
{
	ft_putstr_fd("./pipex: ", 2);
	if (error == 1)
		ft_putendl_fd(ERR_1, 2);
	exit(EXIT_FAILURE);
}

void	ft_free_tab(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab ++;
	}
	/* free(tab); */
}
