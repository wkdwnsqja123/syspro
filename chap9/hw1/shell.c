#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARG_COUNT 100

void parse_command(char *cmd, char **args) {
	int i = 0;
	char *token = strtok(cmd, " \t\n");

	while (token != NULL) {
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
}

void execute_sequential_commands(char *cmds) {
	char *cmd = strtok(cmds, ";");
	while (cmd != NULL) {
		system(cmd);
		cmd = strtok(NULL, ";");
	}
}

void execute_background_command(char *cmd) {
	pid_t pid = fork();
	if (pid == 0) {
		system(cmd);
		exit(0);
	}
}

void handle_io_redirection(char *cmd) {
	char *input_file = NULL;
	char *output_file = NULL;
	char *args[MAX_ARG_COUNT];
	char *cmd_copy = strdup(cmd);
	char *redir_in = strstr(cmd_copy, "<");
	char *redir_out = strstr(cmd_copy, ">");

	if (redir_in != NULL) {
		*redir_in = '\0';
		input_file = strtok(redir_in + 1, " \t\n");
	}

	if (redir_out != NULL) {
		*redir_out = '\0';
		output_file = strtok(redir_out + 1, " \t\n");
	}

	parse_command(cmd_copy, args);

	if (input_file) {
		int fd_in = open(input_file, O_RDONLY);
		if (fd_in == -1) {
			perror("input file open error");
			return;
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}

	if (output_file) {
		int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1) {
			perror("output file open error");
			return;
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}

	execvp(args[0], args);
	perror("execvp failed");
}

int main() {
	char input[MAX_CMD_LENGTH];
	char *args[MAX_ARG_COUNT];
	pid_t pid;

	while(1) {
		printf("[shell] ");
		if (!fgets(input, sizeof(input), stdin)) {
			break;
		}
		
		input[strcspn(input, "\n")] = '\0';
		if (strlen(input) == 0) {
			continue;
		}

		if (input[strlen(input) - 1] == '&') {
			input[strlen(input) - 1] = '\0';
			execute_background_command(input);
			continue;
		}

		if (strchr(input, ';')) {
			execute_sequential_commands(input);
			continue;
		}

		if (strchr(input, '>') || strchr(input, '<')) {
			handle_io_redirection(input);
			continue;
		}

		parse_command(input, args);
		pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
			perror("execvp failed");
			exit(1);
		} else if (pid > 0) {
			wait(NULL);
		} else {
			perror("fork failed");
		}
	}

	return 0;
}
			
