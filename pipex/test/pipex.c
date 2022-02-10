/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:05:36 by athirion          #+#    #+#             */
/*   Updated: 2022/02/09 22:57:34 by BigZozyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "./libft/libft.h"

void child_process(int fd, int end[2], char *cmd)
{
	printf("hello hello hello\n");
	dup2(fd, STDIN_FILENO);
	printf("After 1st dup\n");
	/* dup2(end[1], STDOUT_FILENO); */
	/* printf("After 2nd dup\n"); */
	close(end[0]);
	close(fd);
	printf("Hello\n");
	printf("Execve = %d\n", execve(cmd, &cmd, NULL));
	printf("Goodbye\n");
}

int main(void)
{
	char	*infile_name = "infile";
	char	*outfile_name = "outfile";
	char	*cmd1 = "cat";
	char	*cmd2 = "wc -l";

	int f1 = open(infile_name, O_RDONLY);
	int f2 = open(outfile_name, O_CREAT | O_RDONLY | 0644);

	int fd[2];
	int pid_child1;
	int pid_child2;
	int status;

	pipe(fd);
	pid_child1 = fork();

	if (pid_child1 == 0)
	{
		printf("We are in child1\n");
		child_process(f1, fd, cmd1);
		printf("After child process 1\n");
	}

	pid_child2 = fork();
	
	if (pid_child2 == 0)
	{
		printf("We are in child2\n");
		child_process(f2, fd, cmd2);
		printf("After child process 2\n");
	}

	close(fd[0]);
	close(fd[1]);
		
	waitpid(pid_child1, &status, 0);
	waitpid(pid_child2, &status, 0);
	return (0);
}
