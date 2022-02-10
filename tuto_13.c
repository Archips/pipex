#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/* int main(int argc, char **argv) */
/* { */	
/* 	char cmd[] = "/bin/ls"; */

/* 	char *argVec[] = {"ls", NULL}; */
/* 	char *envVec[] = {NULL}; */

/* 	if (execve(cmd, argVec, envVec) == -1) */
/* 		perror("Error"); */
/* 	return (0); */
/* } */


int main(int argc, char **argv)
{	
	char cmd[] = ft_strjoin("/bin/ls", argv[1]);

	char *argVec[] = {"", NULL};
	char *envVec[] = {NULL};

	if (execve(cmd, argv, envp) == -1)
		perror("Error");
	return (0);
}
