#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int pids[4];
	int fd[4][2];
	int i;
	for (i = 0; i < 3; i ++)
	{
		if (pipe(fd[i]) < 0)
			return (1);
	}
	for (i = 0; i < 4; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
		{
			//child process i
			for (int j = 0; j < 4; j++)
			{
				if (i != j)
					if (close(pipes[j][0]) == -1)
						return (1);
				if (i + 1 != j)
					if (close(pipes[j][1]) == -1)
						retunr (1);
			}
			dup2(pipes[i][0], STDIN_FILENO);
			dup2(pipes[i + 1][1], STDOUT_FILENO);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
		}
	}

	for(int j = 0; j < 4; j ++)
	{
		if (j != 3)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
	
	}

	//Main process
	dup2(pipes[0][1], STDOUT_FILENO);
	dup2(pipes[3][0], STDIN_FILENO);
	close(pipes[0][1]);
	close(pipes[3][0]);

	for (i = 0; i < 4; i ++)
		wait(NULL);
}
