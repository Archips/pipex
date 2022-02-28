#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2];

	pipe(fd);

	printf("Pipe #1 - fd[0] = %d | fd[1] = %d\n", fd[0], fd[1]);

	close(fd[0]);
	close(fd[1]);

	pipe(fd);

	printf("Pipe #2 - fd[0] = %d | fd[1] = %d\n", fd[0], fd[1]);
	
	pipe(fd);

	printf("Pipe #3 - fd[0] = %d | fd[1] = %d\n", fd[0], fd[1]);

	pipe(fd);

	printf("Pipe #4 - fd[0] = %d | fd[1] = %d\n", fd[0], fd[1]);

	
	return (0);
}
