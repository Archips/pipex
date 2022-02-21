/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:10:35 by athirion          #+#    #+#             */
/*   Updated: 2022/02/21 14:01:09 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_all(t_data *data)
{
	int	i;

	i = 0;
	ft_free_tab(data->env_path);
	while (i < data->cmd_id)
	{
		free(data->cmd[i]);
		ft_free_tab(data->arg_cmd[i]);
		i ++;
	}
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
