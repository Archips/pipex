#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		//Child Process
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);	
		if (err == -1)
		{
			printf("Could not find program to execute\n");
			return (1);
		}
	}
	else
	{
		int wstatus;
		//Parent Process
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int status_code = WEXITSTATUS(wstatus);
			if (status_code == 0)
				printf("Success\n");
			else
				printf("Failure\n");
		}
	}
	return (0);
}
