#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int pid = fork();
	if (pid == 0)
	{
		int fd = open("test.txt",  O_WRONLY | O_CREAT);
		if (fd == -1)
			return (2);
		printf("Fd = %d\n", fd);
		int fd2 = dup2(fd, STDOUT_FILENO);
		printf("Fd2 = %d\n", fd2);
		close(fd);
		execlp("ping", "ping", "-c", "1", "google.com", NULL); 

	}
	return (0);
}
