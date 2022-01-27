#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* TO DO : GESTION D'ERREUR */


int main(int argc, char **argv)
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int arr_size = sizeof(arr) / sizeof(int);
	int start;
	int end;
	int fd[2];
	if (pipe(fd) == -1)
		return (1);
	int id = fork();
	if (id == -1)
		return (printf("Error fork\n"), 2);
	if (id == 0)
	{
		start = 0;
		end = arr_size / 2;
	}
	else
	{
		start = arr_size / 2;
		end = arr_size;
	}
	int sum = 0;
	int i;
	for (i = start; i < end; i++)
		sum += arr[i];
	printf("Calculated partial sum: %d\n", sum);

	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}	
	else
	{
		close(fd[1]);
		int sum_child;
		read(fd[0], &sum_child, sizeof(sum_child));
		close(fd[0]);
		int total = sum + sum_child;
		printf("Total sum is %d\n", total);
	}
	return (0);
}
