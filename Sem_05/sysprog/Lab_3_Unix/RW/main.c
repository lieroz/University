#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>

const int READERS_COUNT = 5;
const int WRITERS_COUNT = 3;
const int ITERATIONS = 20;

#define ACTIVE_READER 0
#define WAITING_WRITER 1
#define WRITER_FLAG 2
#define WAITING_READER 3

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


int shm_id = -1;
int sem_id = -1;

char *mem_ptr = (char *) -1;

int childs = 0;

struct sembuf start_reader[5] = {
        {WAITING_READER, 1,  0},
        {WRITER_FLAG,    0,  0},
        {WAITING_WRITER, 0,  0},
        {ACTIVE_READER,  1,  0},
        {WAITING_READER, -1, 0}
};

struct sembuf stop_reader[1] = {
        {ACTIVE_READER, -1, 0}
};

struct sembuf start_writer[4] = {
        {WAITING_WRITER, 1,  0},
        {ACTIVE_READER,  0,  0},
        {WRITER_FLAG,    -1, 0},
        {WAITING_WRITER, -1, 0}
};

struct sembuf stop_writer[1] = {
        {WRITER_FLAG, 1, 0}
};

void start_read()
{
    semop(sem_id, start_reader, 5);
}

void stop_read()
{
    semop(sem_id, stop_reader, 1);
}

void start_write()
{
    semop(sem_id, start_writer, 4);
}

void stop_write()
{
    semop(sem_id, stop_writer, 1);
}

void reader(int id)
{
    while (1) {
        start_read();
        printf("\tReader #%d read: %d\n", id, *mem_ptr);
        stop_read();

        if (*mem_ptr > ITERATIONS) exit(OK);

        sleep(rand() % 3);
    }
}

void writer(int id)
{
    while (1) {
        start_write();
        printf("Writer #%d wrote: %d\n", id, ++(*mem_ptr));
        stop_write();

        if (*mem_ptr > ITERATIONS) exit(OK);

        sleep(rand() % 3);
    }
}

int main(int argc, char *argv[])
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

    if ((sem_id = semget(IPC_PRIVATE, 4, perms)) == -1) {
        pexit("semget", ERR_SEMGET);
    }

    if (semctl(sem_id, 0, SETVAL, 0) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    if (semctl(sem_id, 1, SETVAL, 0) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    if (semctl(sem_id, 2, SETVAL, 1) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    if (semctl(sem_id, 3, SETVAL, 0) < 0) {
        pexit("semctl", ERR_SEMCTL);
    }

    create_processes();
    wait_childs();

    return 0;
}

void pexit(const char *msg, enum errors err_code)
{
    perror(msg);
    exit(err_code);
}

void create_processes()
{
    for (int i = 0; i < WRITERS_COUNT; i++) {
        pid_t pid = fork();
        if (pid < 0) pexit("fork", ERR_FORK);
        if (!pid) {
            writer(i + 1);
        } else {
            childs++;
        }
    }

    for (int i = 0; i < READERS_COUNT; i++) {
        pid_t pid = fork();
        if (pid < 0) pexit("fork", ERR_FORK);
        if (!pid) {
            reader(i + 1);
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