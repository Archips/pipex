#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd[2];
	//fd[0] -> read end
	//fd[1] -> write end
	if (pipe(fd) == -1)
	{
		printf("Pipe error\n");
		return (1);
	}
	int id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int x;
		//scanf("%d\n", &x);
		x = atoi(argv[1]);
			return (write(fd[1], &x, sizeof(int)));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		y *= 10;
		printf("%d\n", y);
		close(fd[0]);
	}
	
	return (0);
}
