#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SLEEP_TIME 1
#define CHILD_COUNT 2

#define RED "\033[91m"
#define ORANGE "\033[93m"
#define END "\033[0m"

int main(void) {
	pid_t pid, result;
	int status, is_parent = 0;
	
	printf("%sparent: ppid = %d pid = %d, group = %d%s\n", ORANGE, getppid(), getpid(), getgid(), END);

	for (unsigned int i = 0; i < CHILD_COUNT; ++i) {
		if ((pid = fork()) == -1) {
			perror("couldn't fork");
			exit(1);
		} else if (pid == 0) {
			sleep(SLEEP_TIME);
			printf("%schild%d: ppid = %d, pid = %d, group = %d%s\n", ORANGE, i + 1, getppid(), getpid(), getgid(), END);
			return 0;
		}
		is_parent = 1;
	}

	if (is_parent) {
		for (unsigned int i = 0; i < CHILD_COUNT; ++i) {
			result = wait(&status);
			if (WIFEXITED(status)) {
				printf("%schild: pid = %d exited with code %d%s\n", ORANGE, result, WEXITSTATUS(status), END);
			} else {
				printf("%schild: pid = %d terminated abnormally%s\n", RED, result, END);
			}
		}
	}

	return 0;
}