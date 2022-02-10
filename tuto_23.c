#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd[2];
	if (pipe(fd) == -1)
		return (1);
	int child1 = fork();
	if (child1 < 0)
		return (2);
	if (child1 == 0)
	{
		//Child Process 1 (PING)
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	int child2 = fork();
	if (child2 < 0)
		return (3);
	if (child2 == 0)
	{
		//Child Process 2 (GREP)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round", NULL);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);

	return (0);
}
