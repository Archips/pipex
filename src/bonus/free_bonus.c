/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:10:35 by athirion          #+#    #+#             */
/*   Updated: 2022/02/26 22:15:34 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_cmd(char *cmd, char **arg_cmd)
{
	if (arg_cmd)
		ft_free_tab(arg_cmd);
	if (cmd)
		free(cmd);
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
