#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

int main(void)
{	
	char cmd[] = "/bin/ls";

	char *argVec[] = {"ls", NULL};
	char *envVec[] = {NULL};

	if (execve(cmd, argVec, envVec) == -1)
		perror("Error");
	return (0);
}



