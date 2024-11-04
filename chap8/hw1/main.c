#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

void print_env_variable(const char *var_name) {
	char *value = getenv(var_name);
	if (value != NULL) {
		printf("%s=%s\n", var_name, value);
	} else {
		printf("%s is nonexistent.\n", var_name);
	}
}

void print_all_env_variables(const char *exclude) {
	char **ptr;
	extern char **environ;

	for (ptr = environ; *ptr != 0; ptr++)
		printf("%s \n", *ptr);
	exit(0);
}

void print_user_id() {
	printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
	printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
}
void print_group_id() {
	printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
	printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
}
void print_process_number() {
	printf("my process number : [%d] \n", getpid());
}
void print_parent_process_number() {
	printf("my parent's process number : [%d] \n", getppid());
}

int main(int argc, char *argv[]) 
{
	if (strcmp(argv[1], "-e") == 0) {
		if (argc < 3) {
			print_all_env_variables(NULL);
		} else {
			print_env_variable(argv[2]);
		}
	} else if (strcmp(argv[1], "-u") == 0) {
		print_user_id();
	} else if (strcmp(argv[1], "-g") == 0) {
		print_group_id();
	} else if (strcmp(argv[1], "-i") == 0) {
		print_process_number();
	} else if (strcmp(argv[1], "-p") == 0) {
		print_parent_process_number();
	} else {
		print_all_env_variables(NULL);
	}
	return 0;
}
