#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int id1;
	id1 = fork();
	int id2;
	id2 = fork();
	if (id1 == 0)
		if (id2 == 0)
			printf("We are process Y\n");
		else
			printf("We are process X\n");
	else
		if (id2 == 0)
			printf("we are process Z\n");
		else
			printf("We are the parent process\n");
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("Wait for a child to finish\n");
	return (0);
}
