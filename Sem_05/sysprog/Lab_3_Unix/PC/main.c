#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdlib.h>

#define RUN_ACCESS 0
#define BUF_EMPTY 1
#define BUF_FULL 2

#define MAX_VAL 100

#define BUF_SIZE 8

unsigned short StartVal[] = {1, BUF_SIZE, 0};


struct sembuf ProdP[2] = {{BUF_EMPTY,  -1, 0},
                          {RUN_ACCESS, -1, 0}};
struct sembuf ProdV[2] = {{BUF_FULL,   1, 0},
                          {RUN_ACCESS, 1, 0}};
struct sembuf ConsP[2] = {{BUF_FULL,   -1, 0},
                          {RUN_ACCESS, -1, 0}};
struct sembuf ConsV[2] = {{BUF_EMPTY,  1, 0},
                          {RUN_ACCESS, 1, 0}};

int main()
{
    int flags = S_IRWXU | S_IRWXG | S_IRWXO;

    int semMas = semget(IPC_PRIVATE, 3, flags);
    if (semMas == -1) {
        perror("Semget error!\n");
        return 1;
    }

    if (semctl(semMas, 0, SETALL, StartVal) == -1) {
        perror("Semctl error!\n");
        return 2;
    }

    int shmId = shmget(IPC_PRIVATE, (BUF_SIZE + 1) * sizeof(int), flags);
    if (shmId == -1) {
        perror("Shmget error!\n");
        return 3;
    }

    pid_t child = 0;
    if ((child = fork()) == -1) {
        perror("Fork error!\n");
        return 1;
    }

    int *pos = (int *) shmat(shmId, 0, 0);
    *pos = 0;

    int *buf = pos + sizeof(int);
    if (buf == (int *) (-1)) {
        perror("Shmat error!\n");
        return 1;
    }

    if (child != 0) {
        while (1) {
            semop(semMas, ConsP, 2);

            *pos = (*pos > 1) ? (*pos - 1) : 0;
            printf("\tПотребитель считал %d из ячейки [%d]\n", buf[*pos], *pos);

            semop(semMas, ConsV, 2);
            sleep(rand() % 5);
        }
    } else {
        int num = 1;
        while (1) {
            semop(semMas, ProdP, 2);

            buf[*pos] = num;
            printf("Производитель записал %d в ячейку [%d]\n", buf[*pos], *pos);

            *pos = (*pos + 1) % (BUF_SIZE);
            semop(semMas, ProdV, 2);

            num = (num + 1) % (MAX_VAL + 1);
            sleep(rand() % 3);
        }
    }

    return 0;
}
