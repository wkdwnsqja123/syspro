#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("parental process start\n");
	if (fork() == 0) {
		execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "stderr");
		exit(1);
	}
	if (fork() == 0) {
		execl("/bin/date", "date", NULL);
		fprintf(stderr,"stderr");
		exit(2);
	}
	if (fork() == 0) {
		execl("/bin/ls", "ls", "-l", NULL);
		fprintf(stderr,"stderr");
		exit(3);
	}
	printf("parental process end\n");
}
