#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

#define SLEEP_TIME 1

#define ORANGE "\033[93m"
#define END "\033[0m"

int main(void)
{
	pid_t pid = fork();

	if (pid == -1) {
		perror("couldn't fork");
		exit(1);
	} else if (pid == 0) {
		sleep(SLEEP_TIME);
  		printf("%schild: ppid = %d, pid = %d, group = %d%s\n", ORANGE, getppid(), getpid(), getgid(), END);
  		return 0;
  	} else {
  		printf("%sparent: chpid = %d, pid = %d, group = %d%s\n", ORANGE, pid, getpid(), getgid(), END);
  		return 0;
	}
}
