/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:10:35 by athirion          #+#    #+#             */
/*   Updated: 2022/02/26 16:11:12 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_all(t_data *data)
{
	ft_free_tab(data->env_path);
}

void	ft_free_tab(char **tab)
{
	char	**temp;

	temp = tab;
	while (*tab)
	{
		free(*tab);
//		*tab = NULL;
		tab ++;
	}
	free(temp);
//	temp = NULL;
}

/* void	ft_free_pipe(t_data *data) */
/* { */
/* 	int	i; */

/* 	i = data->nb_cmd; */
/* 	while (i >=0) */
/* 	{ */
/* 		free(data->pipe[i]); */
/* 		i --; */
/* 	} */
/* 	free(data->pipe); */
/* 	data->pipe = NULL; */
/* } */
