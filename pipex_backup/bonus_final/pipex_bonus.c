/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:16:01 by athirion          #+#    #+#             */
/*   Updated: 2022/02/23 20:28:32 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	if (ft_check_args(argc, argv))
	{

		printf("It's ok\n");
		exit(EXIT_SUCCESS);
	}
	ft_putendl_fd("pipex: Error: Arguments missing", 2);
	exit(EXIT_FAILURE);
}
