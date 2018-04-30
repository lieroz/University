#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define DATA "Hello from client! This is a simple demonstration programm."
#define SERVER_PORT 5001
#define BUFFER_SIZE 1024

void die(const char *);
void pdie(const char *);

int main(int argc, char *argv[]) {
    int i, sd, clientLen;
    struct sockaddr_in server, client;
    struct hostent *hp;
    char buf[BUFFER_SIZE];

    if (argc != 2) {
        die("Usage: client hostname");
    }

    for (i = 0; i < 100; ++i) {
        if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            pdie("Opening stream socket");
        }

        bzero((char *) &server, sizeof(server));
        server.sin_family = AF_INET;
        if ((hp = gethostbyname(argv[1])) == NULL) {
            sprintf(buf, "%s: unknown host\n", argv[1]);
            die(buf);
        }

        bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
        server.sin_port = htons((u_short) SERVER_PORT);

        if (connect(sd, (struct sockaddr *) &server, sizeof(server)) < 0){
            pdie("Connecting stream socket");
        }

        clientLen = sizeof(client);
        if (getsockname(sd, (struct sockaddr *) &client, &clientLen)) {
            pdie("Getting socket name");
        }

        if (clientLen != sizeof(client)) {
            die("getsockname() overwrote name structure");
        }

        printf("Client socket has port %hu\n", ntohs(client.sin_port));

        if (write(sd, DATA, sizeof(DATA)) < 0) {
            pdie("Writing on stream socket");
        }

        bzero(buf, sizeof(buf));
        if (read(sd, buf, BUFFER_SIZE) < 0) {
            pdie("Reading stream message");
        }

        printf("C: %s\n", buf);
        close(sd);
    }

    exit(0);
}

void pdie(const char *mesg) {

    perror(mesg);
    exit(1);
}

void die(const char *mesg) {

    fputs(mesg, stderr);
    fputc('\n', stderr);
    exit(1);
}