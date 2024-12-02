#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100

int main() {
    int fd;
    pid_t pid;
    char message[MAXLINE];
    mkfifo("myPipe", 0660);
    pid = fork();
    if (pid > 0) {
        fd = open("myPipe", O_WRONLY);
        sprintf(message, "Hello from PID %d", getpid());
        write(fd, message, strlen(message) + 1);
        printf("Send: [%d] %s\n", getpid(), message);
        close(fd);
    } else if (pid == 0) {
        fd = open("myPipe", O_RDONLY);
        read(fd, message, MAXLINE);
        printf("Recv: [%d] %s\n", getpid(), message);
        close(fd);
    }
    return 0;
}

