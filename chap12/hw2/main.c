#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#define MAXLINE 100

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;
    char message[MAXLINE];

    pipe(pipe_fd);
    printf("parent process start\n");

    pid1 = fork();
    if (pid1 == 0) {
        close(pipe_fd[0]);
        while (1) {
            printf("input string: ");
            fgets(message, MAXLINE, stdin);
            message[strcspn(message, "\n")] = '\0';
            write(pipe_fd[1], message, strlen(message) + 1);
            if (strcmp(message, "exit") == 0) break;
        }
        close(pipe_fd[1]);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(pipe_fd[1]);
        while (1) {
            read(pipe_fd[0], message, MAXLINE);
            if (strcmp(message, "exit") == 0) break;
            to_uppercase(message);
            printf("%s\n", message);
        }
        close(pipe_fd[0]);
        exit(0);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}

