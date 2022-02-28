#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd[3][2];
	int i;
	for (i = 0; i < 3; i ++)
	{
		if (pipe(fd[i]) < 0)
			return (1);
	}

	int pid1 = fork();
	if (pid1 == 0)
	{
		//child process 1;
		if (close(fd[0][1]) == -1)
			return (1);
		if (close(fd[1][0]) == -1)
			return (1);
		if (close(fd[2][1]) == -1)
			return (1);
		if (close(fd[2][0]) == -1)
			return (1);
		dup2(fd[0][0], STDIN_FILENO);
		dup2(fd[1][1], STDOUT_FILENO);		
		if (close(fd[0][0]) == -1)
			return (1);
		if (close(fd[1][1]) == -1)
			return (1);
	}
	
	int pid2 = fork();
	if (pid2 == 0)
	{
		//child process 2;
		if (close(fd[0][1]) == -1)
			return (1);
		if (close(fd[0][0]) == -1)
			return (1);
		if (close(fd[1][1]) == -1)
			return (1);
		if (close(fd[2][0]) == -1)
			return (1);
		dup2(fd[1][0], STDIN_FILENO);
		dup2(fd[2][1], STDOUT_FILENO);		
		if (close(fd[1][0]) == -1)
			return (1);
		if (close(fd[2][1]) == -1)
			return (1);
	}
	//parent process 
	if (close(fd[0][1]) == -1)
		return (1);
	if (close(fd[0][0]) == -1)
		return (1);
	if (close(fd[1][1]) == -1)
		return (1);
	if (close(fd[1][0]) == -1)
		return (1);
	dup2(fd[0][1], STDOUT_FILENO);		
	dup2(fd[2][0], STDIN_FILENO);
	if (close(fd[0][1]) == -1)
		return (1);
	if (close(fd[2][0]) == -1)
		return (1);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
