#include <stdio.h>
#include <stdlib.h>

int main() {
	int childpid;
	if ((childpid = fork()) == -1) {
		perror("Can't fork!\n");
		exit(1);
	}
	else if (childpid == 0) {
	    while (1) {
		    printf("childpid = %d\n", getpid());
		}
		return 0;
	}
	else {
	    while (1) {
		    printf("parentpid = %d\n", getpid());
		}
	}
	return 0;
}
