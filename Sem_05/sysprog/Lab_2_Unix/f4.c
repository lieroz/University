#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD_COUNT 2

#define RED "\033[91m"
#define ORANGE "\033[93m"
#define END "\033[0m"

int main(void)
{
    pid_t pid, result;
    int fd[2];
    int status, is_parent = 0;
    char *input = "Hello from child %d!\n";
    int msg_len = strlen(input);
    char output[msg_len];
    
    if (pipe(fd) < 0) {
        perror("couldn't make pipe");
        exit(2);
    }

    printf("%sparent: ppid = %d pid = %d, group = %d%s\n", ORANGE, getppid(), getpid(), getgid(), END);

    for (unsigned int i = 0; i < CHILD_COUNT; ++i) {
        if ((pid = fork()) == -1) {
            perror("couldn't fork");
            exit(1);
        } else if (pid == 0) {
            printf("%schild: ppid = %d, pid = %d, group = %d%s\n", ORANGE,  getppid(), getpid(), getgid(), END);
            close(fd[1]);
            write(STDOUT_FILENO, output, read(fd[0], output, msg_len));
            return 0;
        }
        is_parent = 1;
    }

    if (is_parent) {
        for (unsigned int i = 0; i < CHILD_COUNT; ++i) {
            close(fd[0]);
            char message[msg_len];
            sprintf(message, input, i);
            write(fd[1], message, msg_len);
            result = wait(&status);

            if (WIFEXITED(status)) {
                printf("%schild: pid = %d exited with code %d%s\n", ORANGE, result, WEXITSTATUS(status), END);
            } else {
                printf("%schild: pid = %d terminated abnormally%s\n", RED, result, END);
            }
        }
    }
}
