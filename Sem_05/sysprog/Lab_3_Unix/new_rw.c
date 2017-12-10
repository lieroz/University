#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define READERS_COUNT 5
#define WRITERS_COUNT 3

const int iterations = 5; // how many times each writer modifies memory

int active_readrs = 0;
int writing = 0;

key_t ipc_key;
int sem_id = -1;
int shm_id = -1;
int *mem_ptr = NULL;

pid_t child_pids[READERS_COUNT + WRITERS_COUNT];
int childs = 0;

enum errors {OK = 0, ERR_FORK};

void pexit(const char *msg, errors err_code)
{
    perror(msg);
    exit(err_code);
}


void start_read()
{
}

void stop_read()
{
}

void start_write()
{
}

void stop_write()
{
}

void reader(int id)
{
    while (*mem_ptr < iterations * WRITERS_COUNT) {
        start_read();
        printf("Writer #%d wrote: %d\n", id, *mem_ptr);
        stop_read();
    }
}

void writer(int id)
{
    for (int i = 0; i < WRITERS_COUNT; i++) {
        start_write();
        printf("\tReader #%d read: %d\n", id, *(++mem_ptr));
        stop_write();
    }
}

void create_processes()
{
    for (int i = 0; i < WRITERS_COUNT; i++) {
        child_pids[i] = fork();
        if (child_pids[i] < 0) pexit("fork", ERR_FORK);
        if (!child_pids[i]) {
            writer(i + 1);
            exit(OK);
        } else {
            childs++;
        }
    }
    
    int proc_count = childs;

    for (int i = 0; i < READERS_COUNT; i++) {
        child_pids[proc_count - 1] = fork();
        if (child_pids[proc_count] < 0) pexit("fork", ERR_FORK);
        if (!child_pids[proc_count - 1]) {
            reader(i + 1);
            exit(OK);
        } else {
            childs++;
        }
    }
}

void wait_childs()
{
    for (int i = 0; i < childs; i ++ ) {
        wait(0);
    }
}

void cleanup()
{
    for (int i = 0; i < childs; i++) {
        if (child_pids[i] > 0) kill(child_pids[i], SIGTERM);
    }
}

int main()
{
    int perms = IPC_CREAT | S_IRWXU | S_IRWXG | S_IRWXO;

    atexit(cleanup);
    create_processes();
    wait_childs();

    return 0;
}
