/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:05:36 by athirion          #+#    #+#             */
/*   Updated: 2022/02/08 22:43:28 by BigZozyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "./libft/libft.h"

/* void	pipex(int f1, int f2) */
/* { */
/* 	int end[2]; */
/* 	int pid; */

/* 	if (pipe(end) == -1) */
/* 		return (1); */
/* 	if ((pid = fork()) == -1) */
/* 		return (perror("Fork: ")); */	
/* 	if (pid == 0) */
/* 		child_process(f1, cmd1); */
/* 	else */
/* 		parent_process(f2, cmd2); */
/* } */

int main(int argc, char **argv)
{
	char	*infile_name;
	char	*outfile_name;
	int		cmds;
	
	if (argc < 3)
	{
		printf("Error - Arguments missing\n");
		exit(EXIT_FAILURE);
	}
	cmds = argc - 3;

	infile_name = ft_strdup(argv[1]);
	outfile_name = ft_strdup(argv[argc - 1]);
	printf("Infile : %s | Outfile : %s\n", infile_name, outfile_name);
	return (0);
}
