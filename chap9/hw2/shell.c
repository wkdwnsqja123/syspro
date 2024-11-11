#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARG 64
#define DELIM " \t\r\n\a"

void parse_input(char *input, char **args) {
    char *token;
    int i = 0;

    token = strtok(input, DELIM);
    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, DELIM);
    }
    args[i] = NULL;
}

void shell_loop() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *args[MAXARG];
    int background;

    while (1) {
        printf("[Shell] ");
        fflush(stdout);

        read = getline(&line, &len, stdin);
        if (read == -1) {
            if (feof(stdin)) {
                break;
            } else {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        line[strcspn(line, "\n")] = 0;

        background = 0;
        if (line[strlen(line) - 1] == '&') {
            background = 1;
            line[strlen(line) - 1] = '\0';
        }

        parse_input(line, args);

        if (args[0] == NULL) {
            continue;
        }
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        } else {
            if (background == 0) {
                waitpid(pid, NULL, 0);
            }
        }
    }

    free(line);
}

int main() {
    shell_loop();
    return 0;
}

