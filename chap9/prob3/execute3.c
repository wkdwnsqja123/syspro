#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int child, pid, status;
	pid = fork();
	if (pid == 0) {
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s:stderr\n", argv[1]);
	} else {
		child = wait(&status);
		printf("[%d] child process %d end \n", getpid(), pid);
		printf("\tend code %d \n", status>>8);
	}
}

