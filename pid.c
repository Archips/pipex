#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int id;
	id = fork();
	if (id == 0)
		sleep(1);
	printf("CURRENT ID : %d | PARENT ID : %d\n", getpid(), getppid());
	if (id != 0)
		wait(NULL);
	return(0);
}
