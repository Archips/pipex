#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
	int p1[2];
	int p2[2];
	if (pipe(p1) == -1)
		return (1);
	if (pipe(p2) == -1)
		return (1);
	int pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		close(p1[0]);
		close(p2[1]);	
		//Child Process
		int x;
		read(p2[0], &x, sizeof(x));
		printf("Received  %d\n", x);
		x *= 4;
		write(p1[1], &x, sizeof(x));
		printf("Wrote  %d\n", x);
		close(p1[1]);
		close(p2[0]);
	}
	else
	{
		close(p1[1]);
		close(p2[0]);
		//Parent process
		srand(time(NULL));
		int y = rand() % 10;
		write(p2[1], &y, sizeof(y));
		printf("Wrote %d\n", y);
		read(p1[0], &y, sizeof(y));
		printf("Result %d\n", y);
		close(p1[0]);
		close(p2[1]);
		wait(NULL);
	}
	close(p1[0]);
	close(p1[1]);
	return (0);
}
