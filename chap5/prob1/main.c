#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int arge, char *argv[])
{
	int fd;

	if ((fd = open(argv[1], O_RDWR)) == -1)
		printf("File Open Error\n");
	else printf("file %s Open Success : %d\n", argv[1], fd);

	close(fd);
	exit(0);
}
