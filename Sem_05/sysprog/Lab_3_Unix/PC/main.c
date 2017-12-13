#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

const int PRODUCERS_COUNT = 3;
const int CONSUMERS_COUNT = 5;

enum errors
{
    OK = 0,
    ERR_FORK,
    ERR_SHMGET,
    ERR_SHMAT,
    ERR_SEMGET,
    ERR_SEMCTL
};

void pexit(const char *, enum errors);

void create_processes();

void wait_childs();

void cleanup();

#define RUN_ACCESS 0
#define BUF_EMPTY 1
#define BUF_FULL 2

#define MAX_VAL 100

#define BUF_SIZE 8

unsigned short start_value[] = {1, BUF_SIZE, 0};

struct sembuf producer_p[2] = {
        {BUF_EMPTY,  -1, 0},
        {RUN_ACCESS, -1, 0}
};

struct sembuf producer_v[2] = {
        {BUF_FULL,   1, 0},
        {RUN_ACCESS, 1, 0}
};

struct sembuf consumer_p[2] = {
        {BUF_FULL,   -1, 0},
        {RUN_ACCESS, -1, 0}
};

struct sembuf consumer_v[2] = {
        {BUF_EMPTY,  1, 0},
        {RUN_ACCESS, 1, 0}
};

int shm_id = -1;
int sem_id = -1;

int *mem_ptr = (int *) -1;
int *buf = (int *) -1;
int *num = NULL;

int childs = 0;

void producer(int id)
{
    while (1) {
        semop(sem_id, producer_p, 2);

        buf[*mem_ptr] = *num;
        printf("Producer #%d wrote %d in cell [%d]\n", id, buf[*mem_ptr], *mem_ptr);

        *mem_ptr = (*mem_ptr + 1) % (BUF_SIZE);
        semop(sem_id, producer_v, 2);

        *num = (*num + 1) % (MAX_VAL + 1);
        sleep((unsigned int) (rand() % 3)); // NOLINT
    }
}

void consumer(int id)
{
    while (1) {
        semop(sem_id, consumer_p, 2);

        *mem_ptr = (*mem_ptr > 1) ? (*mem_ptr - 1) : 0;
        printf("\tConsumer #%d read %d from cell [%d]\n", id, buf[*mem_ptr], *mem_ptr);

        semop(sem_id, consumer_v, 2);
        sleep((unsigned int) (rand() % 5)); // NOLINT
    }
}

int main()
{
    int perms = IPC_CREAT | S_IRWXU | S_IRWXG | S_IRWXO;

    atexit(cleanup);

    num = mmap(NULL, sizeof *num, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *num = 1;

    if ((shm_id = shmget(IPC_PRIVATE, (BUF_SIZE + 1) * sizeof(int), perms)) == -1) {
        pexit("shmget", ERR_SHMGET);
    }

    if ((mem_ptr = shmat(shm_id, NULL, 0)) == (void *) -1) {
        pexit("shmat", ERR_SHMAT);
    }

    *mem_ptr = 0;

    if ((buf = mem_ptr + sizeof(int)) == (int *) (-1)) {
        pexit("shmat", ERR_SHMAT);
    }

    if ((sem_id = semget(IPC_PRIVATE, 3, perms)) == -1) {
        pexit("semget", ERR_SEMGET);
    }

    if (semctl(sem_id, 0, SETALL, start_value) == -1) {
        pexit("semctl", ERR_SEMCTL);
    }

    create_processes();
    wait_childs();

    return OK;
}

void pexit(const char *msg, enum errors err_code)
{
    perror(msg);
    exit(err_code);
}

void create_processes()
{
    for (int i = 0; i < PRODUCERS_COUNT; i++) {
        pid_t pid = fork();
        if (pid < 0) pexit("fork", ERR_FORK);
        if (!pid) {
            producer(i + 1);
        } else {
            childs++;
        }
    }

    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        pid_t pid = fork();
        if (pid < 0) pexit("fork", ERR_FORK);
        if (!pid) {
            consumer(i + 1);
        } else {
            childs++;
        }
    }
}

void wait_childs()
{
    while (childs--) wait(NULL);
}


void cleanup()
{
    if (mem_ptr != (void *) -1) shmdt(mem_ptr);
    if (sem_id >= 0) semctl(sem_id, 0, IPC_RMID);
    if (shm_id >= 0) shmctl(shm_id, IPC_RMID, 0);
}

#pragma clang diagnostic pop