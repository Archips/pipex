#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int arr[] = {500, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int len = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
		return (1);
	int id = fork();
	if (id == 0)
	{
		start = 0;
		end = start + len/2;
	}
	else
	{
		start = len / 2;
		end = len;
	}
	int sum = 0;
	int i;
	for (i = start; i < end; i++)
		sum += arr[i];
	printf("Partial sum = %d\n", sum);

	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int total;
		read(fd[0], &total, sizeof(total));
		close(fd[0]);
		total += sum;
		printf("TOTAL : %d\n", total);
		wait(NULL);
	}

	
	return (0);
}
			
