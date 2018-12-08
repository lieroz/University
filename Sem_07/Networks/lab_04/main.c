#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <errno.h>
#include <memory.h>

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct pollfd pollfd_t;

static const short port = 8080;
static const int backlog = 1 << 5;
static const int desc_count = 1 << 7;
static const int timeout = 1 << 16;
static const int msg_size = 1 << 10;

void error_log(const char *msg, int *code)
{
    perror(msg);
    *code = -1;
}

void init_addr(sockaddr_in_t *addr)
{
    memset(addr, 0, sizeof(sockaddr_in_t));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);
}

void server_loop(int listen_sd, pollfd_t *fds)
{
    int code = 0, msg_len;
    int nfds = 1, curr_nfds;
    int new_sd;
    char close_conn, shrink_fds = 0;
    char msg[msg_size];

    memset(fds, 0, sizeof(fds));
    fds[0].fd = listen_sd;
    fds[0].events = POLLIN;

    while (code != -1) {
        if ((code = poll(fds, nfds, timeout)) < 0) {
            error_log("poll() failed", &code);
        } else if (!code) {
            error_log("poll() timed out, end server", &code);
        } else {
            curr_nfds = nfds;

            for (int i = 0; i < curr_nfds; ++i) {
                if (!fds[i].revents) continue;

                if (fds[i].revents ^ POLLIN) {
                    error_log("revents is not POLLIN which is unexpected", &code);
                    break;
                }

                if (!(fds[i].fd ^ listen_sd)) {
                    do {
                        if ((new_sd = accept(listen_sd, 0, 0)) < 0) {
                            if (errno != EWOULDBLOCK) error_log("accept() failed", &new_sd);
                        } else {
                            fds[nfds].fd = new_sd;
                            fds[nfds].events = POLLIN;
                            ++nfds;
                        }
                    } while (new_sd != -1);
                } else {
                    close_conn = 0;

                    do {
                        if ((msg_len = recv(fds[i].fd, msg, sizeof(msg) - 1, 0)) < 0) {
                            if (errno != EWOULDBLOCK) {
                                error_log("recv() failed", &msg_len);
                                close_conn = 1;
                            }
                        } else if (!msg_len) {
                            printf("Connection closed.\n");
                            close_conn = 1;
                        } else {
                            msg[msg_len] = '\0';
                            printf("Msg: %s\n", msg);
                        }
                    } while (msg_len > 0);

                    if (close_conn) {
                        close(fds[i].fd);
                        fds[i].fd = -1;
                        shrink_fds = 1;
                    }
                }
            }
        }

        if (shrink_fds) {
            shrink_fds = 0;

            for (int i = 0; i < nfds; ++i) {
                if (fds[i].fd == -1) {

                    for (int j = 1; j < nfds; ++j) {
                        fds[j].fd = fds[j+1].fd;
                    }

                    --i;
                    --nfds;
                }
            }
        }
    }

    for (int i = 0; i < nfds; ++i) {
        if (fds[i].fd >= 0) close(fds[i].fd);
    }
}

int main()
{
    int code = 0, on = 1;
    int listen_sd = -1;
    sockaddr_in_t addr;
    pollfd_t fds[desc_count];

    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error_log("socket() failed", &code);
        goto exit;
    }

    if (setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        error_log("setsockopt() failed", &code);
        goto exit;
    }

    if (ioctl(listen_sd, FIONBIO, &on) < 0) {
        error_log("ioctl() failed", &code);
        goto exit;
    }

    init_addr(&addr);
    if (bind(listen_sd, (sockaddr_t *) &addr, sizeof(addr)) < 0) {
        error_log("bind() failed", &code);
        goto exit;
    }

    if (listen(listen_sd, backlog) < 0) {
        error_log("listen() failed", &code);
        goto exit;
    }
    
    server_loop(listen_sd, fds);

exit:
    if (close(listen_sd) < 0) {
        error_log("close() failed", &code);
    }

    return code;
}
