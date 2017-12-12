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
#include <sys/mman.h>

#define DEBUG

#define READERS_COUNT 5
#define WRITERS_COUNT 3

const int iterations = 5; // how many times each writer modifies memory

int sem_id = -1;
int shm_id = -1;
int *mem_ptr = (void *) -1;

pid_t child_pids[READERS_COUNT + WRITERS_COUNT];
int childs = 0;

enum errors {OK = 0, ERR_FORK, ERR_SHMGET, ERR_SHMAT, ERR_SEMGET, ERR_SEMCTL};

const int semaphore_count = 3; // includes three variables lower

#define BINARY_SEM 0
#define WRITER_SEM 1
#define READER_SEM 2

struct sembuf lock[] = {{BINARY_SEM, 0, 0}, {BINARY_SEM, 1, 0}};
struct sembuf unlock[] = {{BINARY_SEM, -1, 0}};

struct sembuf read_event[] = {{READER_SEM, 0, IPC_NOWAIT}};
struct sembuf write_event[] = {{WRITER_SEM, 0, IPC_NOWAIT}};

struct sembuf wait_read[] = {{READER_SEM, 0, 0}};
struct sembuf wait_write[] = {{WRITER_SEM, 0, 0}};

struct sembuf lock_read[] = {{READER_SEM, 0, 0}, {READER_SEM, 1, 0}};
struct sembuf unlock_read[] = {{READER_SEM, -1, 0}};

struct sembuf lock_write[] = {{WRITER_SEM, 0, 0}, {WRITER_SEM, 1, 0}};
struct sembuf unlock_write[] = {{WRITER_SEM, -1, 0}};

static int *active_readers = NULL;
static int *writing = NULL; 

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

    if (*writing || semop(sem_id, write_event, 1) == EAGAIN) {
        semop(sem_id, wait_read, 1);
    }

    semop(sem_id, lock, 2);
    semop(sem_id, lock_read, 2);
    (*active_readers)++;

    pdebug("left start_read...");
}

void stop_read()
{
    pdebug("entered stop_read...");

    (*active_readers)--;

    if (*active_readers == 0) {
        semop(sem_id, unlock_write, 1);
    }

    semop(sem_id, unlock, 1);

    pdebug("left stop_read...");
}

void start_write()
{
    pdebug("entered start_write...");

    if (*writing || *active_readers > 0) {
        semop(sem_id, wait_write, 1);
    }

    semop(sem_id, lock, 2);
    semop(sem_id, lock_write, 2);
    *writing = 1;

    pdebug("left start_write...");
}

void stop_write()
{
    pdebug("entered stop_write...");

    *writing = 0;

    if (semop(sem_id, read_event, 1) == EAGAIN) {
        semop(sem_id, unlock_read, 1);
    } else {
        semop(sem_id, unlock_write, 1);
    }

    semop(sem_id, unlock, 1);

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
    if (active_readers) munmap(active_readers, sizeof *active_readers);
    if (writing) munmap(writing, sizeof *writing);
}

int main()
{
    int perms = IPC_CREAT | S_IRWXU | S_IRWXG | S_IRWXO;

    active_readers = (int *) mmap(NULL, sizeof *active_readers, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *active_readers = 0;

    writing = (int *) mmap(NULL, sizeof *writing, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);;
    *writing = 0;
    
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

    if (semctl(sem_id, BINARY_SEM, SETVAL, 0) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    if (semctl(sem_id, WRITER_SEM, SETVAL, 0) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    if (semctl(sem_id, READER_SEM, SETVAL, 1) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    create_processes();
    wait_childs();

    return 0;
}
