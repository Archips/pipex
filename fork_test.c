#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int id;	
	id = fork();
	/* printf("HELLO HOW YA DOIN ? : %d\n", id); */
	if (id == 0)
		printf("CHILD PROCESS\n");
	else
	{
		fork();
		printf("MAIN PROCESS\n");
	}
	/* fork(); */
	/* fork(); */
	/* fork(); */
	/* fork(); */
	/* printf("Hello hello hello\n"); */

	return (0);
}
