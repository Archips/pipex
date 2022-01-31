#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	if (mkfifo("myfifo1", 0777) == -1)
	{
		if (errno != EEXIST)
			return (1);
	}
	int fd = open("myfifo1", O_WRONLY);
	int x = 100;
	write(fd, &x, sizeof(x));
	close(fd);
	return (0);
}
