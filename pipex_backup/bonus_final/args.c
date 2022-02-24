/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:22:59 by athirion          #+#    #+#             */
/*   Updated: 2022/02/23 11:26:40 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_args(int argc, char **argv)
{
	if (ft_is_heredoc(argv[1]) && argc >= 6)
		return (1);
	else if (!ft_is_heredoc(argv[1]) && argc >= 5)
		return (1);
	return (0);
}
