#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	int id1;
	int id2;
	id1 = fork();
	id2 = fork();
	if (id1 == 0)
		if (id2 == 0)
			printf("We are process y\n");
		else
			printf("We are process x\n");
	else
		if (id2 == 0)
			printf("We are process z\n");
		else
			printf("We are the parent process!\n");
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("Waited for the child to finish\n");
	return(0);
}
