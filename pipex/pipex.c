/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:05:36 by athirion          #+#    #+#             */
/*   Updated: 2022/02/04 23:11:49 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	pipex(int f1, int f2)
{
	int end[2];
	int pid;

	if (pipe(end) == -1)
		return (1);
	if ((pid = fork()) == -1)
		return (perror("Fork: "));	
	if (pid == 0)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}
