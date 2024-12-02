#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 100

int main() {
    int fd, length, i;
    char message[MAXLINE];
    mkfifo("myPipe", 0660);
    sprintf(message, "Hello from PID %d", getpid());
    length = strlen(message) + 1;
    do {
        fd = open("myPipe", O_WRONLY);
        if (fd == -1) sleep(1);
    } while (fd == -1);
    for (i = 0; i <= 3; i++) {
        if (write(fd, message, length) != length) {
            close(fd);
            return 1;
        }
        sleep(3);
    }
    close(fd);
    return 0;
}


