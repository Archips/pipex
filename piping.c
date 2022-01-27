#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* fd[0] - read */
/* fd[1] - write */
	

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		int fd[2];
		int id;
	
		if (pipe(fd) == 1)
		{
			printf("Error\n");
			return (1);
		}
	
		id = fork();

		if (id == 0)
		{
			close(fd[0]);
			int x;
			x = atoi(argv[1]);
			if (write(fd[1], &x, sizeof(int)) == -1)
				return (printf("ERROR\n"), 2);
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			int y;
			if (read(fd[0], &y, sizeof(int)) == -1)
				return (printf("ERROR\n"), 2);
			printf("%d\n", y);
			close(fd[0]);
		}
	}
	return (0);
}
