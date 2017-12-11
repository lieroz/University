#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define DEBUG

#define READERS_COUNT 5
#define WRITERS_COUNT 3

const int iterations = 5; // how many times each writer modifies memory

int sem_id = -1;
int shm_id = -1;
int *mem_ptr = (void *) -1;

pid_t child_pids[READERS_COUNT + WRITERS_COUNT];
int childs = 0;

enum errors {OK = 0, ERR_FORK, ERR_SHMGET, ERR_SHMAT, ERR_SEMGET};

const int semaphore_count = 3; // includes three variables lower

#define BINARY_SEM 0
#define WRITER_SEM 1
#define READER_SEM 2

struct sembuf lock_binary[] = {{BINARY_SEM, 1, 0}};
struct sembuf unlock_binary[] = {{BINARY_SEM, -1, 0}};

struct sembuf check_is_reading[] = {{READER_SEM, 0, IPC_NOWAIT}};
struct sembuf check_is_writing[] = {{WRITER_SEM, 0, IPC_NOWAIT}};

struct sembuf wait_can_read[] = {{READER_SEM, 0, 0}};
struct sembuf wait_can_write[] = {{WRITER_SEM, 0, 0}};

struct sembuf set_can_read_inc[] = {{WRITER_SEM, 1, 0}};
struct sembuf set_can_write_inc[] = {{READER_SEM, 1, 0}};

int active_readers = 0;
int writing = 0;

void pexit(const char *msg, enum errors err_code)
{
    perror(msg);
    exit(err_code);
}

void pdebug(const char *msg)
{
#ifdef DEBUG
    printf("\033[91m%s\n\033[0m", msg);
#endif
}

void start_read()
{
    pdebug("entered start_read...");

    if (writing || semop(sem_id, check_is_writing, 1) != EAGAIN) {
        semop(sem_id, wait_can_read, 1);
    }

    semop(sem_id, lock_binary, 1);
    active_readers++;
    semop(sem_id, set_can_read_inc, 1);

    pdebug("left start_read...");
}

void stop_read()
{
    pdebug("entered stop_read...");

    active_readers--;

    if (active_readers == 0) {
        semop(sem_id, set_can_write_inc, 1);
    }

    semop(sem_id, unlock_binary, 1);

    pdebug("left stop_read...");
}

void start_write()
{
    pdebug("entered start_write...");

    if (writing || active_readers > 0) {
        semop(sem_id, wait_can_write, 1);
    }

    semop(sem_id, lock_binary, 1);
    writing = 1;

    pdebug("left start_write...");
}

void stop_write()
{
    pdebug("entered stop_write...");

    writing = 0;

    if (semop(sem_id, check_is_reading, 1) != EAGAIN) {
        semop(sem_id, set_can_read_inc, 1);
    } else {
        semop(sem_id, set_can_write_inc, 1);
    }

    semop(sem_id, unlock_binary, 1);

    pdebug("exited stop_write...");
}

void reader(int id)
{
    while (*mem_ptr < iterations * WRITERS_COUNT) {
        start_read();
        printf("\tReader #%d read: %d\n", id, *mem_ptr);
        stop_read();
    }
}

void writer(int id)
{
    for (int i = 0; i < iterations; i++) {
        start_write();
        printf("Writer #%d wrote: %d\n", id, ++(*mem_ptr));
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
        wait(NULL);
    }
}

void cleanup()
{
    for (int i = 0; i < childs; i++) {
        if (child_pids[i] > 0) kill(child_pids[i], SIGTERM);
    }

    if (mem_ptr != (void *) -1) shmdt(mem_ptr);
    if (sem_id >= 0) semctl(sem_id, 0, IPC_RMID);
    if (shm_id >= 0) shmctl(shm_id, IPC_RMID, 0);
}

int main()
{
    int perms = IPC_CREAT | S_IRWXU | S_IRWXG | S_IRWXO;
    
    atexit(cleanup);

    if ((shm_id = shmget(IPC_PRIVATE, sizeof(int), perms)) == -1) {
        pexit("shmget", ERR_SHMGET);
    }

    if ((mem_ptr = shmat(shm_id, NULL, 0)) == (void *) -1) {
        pexit("shmat", ERR_SHMAT);
    }

    *mem_ptr = 0;
    
    if ((sem_id = semget(IPC_PRIVATE, semaphore_count, perms)) == -1) {
        pexit("semget", ERR_SEMGET);
    }

    create_processes();
    wait_childs();

    return 0;
}
