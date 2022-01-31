#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int id = fork();
	if (id == 0)
		sleep(1);
	printf("Curent ID -> %d | Parent ID -> %d\n", getpid(), getppid());
	if (id != 0)
		wait(NULL);
	return (0);
}
