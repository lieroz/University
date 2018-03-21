#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

static int running = 0;
static int delay = 1;
static int counter = 0;
static char *pid_file_name = "/var/run/my_daemon.pid";
static char *log_file_name = "/var/log/my_daemon.log";
static int pid_fd = -1;
static char *app_name = NULL;
static FILE *log_stream;

/**
 * \brief Callback function for handling signals.
 * \param   sig identifier of signal
 */
void handle_signal(int sig)
{
    if (sig == SIGINT) {
        fprintf(log_stream, "Debug: stopping daemon ...\n");
        /* Unlock and close lockfile */
        if (pid_fd != -1) {
            lockf(pid_fd, F_ULOCK, 0);
            close(pid_fd);
        }
        /* Try to delete lockfile */
        if (pid_file_name != NULL) {
            unlink(pid_file_name);
        }
        running = 0;
        /* Reset signal handling to default behavior */
        signal(SIGINT, SIG_DFL);
    } else if (sig == SIGCHLD) {
        fprintf(log_stream, "Debug: received SIGCHLD signal\n");
    }
}

/**
 * \brief This function will daemonize this app
 */
static void daemonize(void)
{
    pid_t pid = 0;
    int fd;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Success: Let the parent terminate */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* On success: The child process becomes session leader */
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    /* Ignore signal sent from child to parent process */
    signal(SIGCHLD, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Success: Let the parent terminate */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    for (fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--) {
        close(fd);
    }

    /* Reopen stdin (fd = 0), stdout (fd = 1), stderr (fd = 2) */
    stdin = fopen("/dev/null", "r");
    stdout = fopen("/dev/null", "w+");
    stderr = fopen("/dev/null", "w+");

    char str[256];
    pid_fd = open(pid_file_name, O_RDWR | O_CREAT, 0640);
    if (pid_fd < 0) {
        /* Can't open lockfile */
        exit(EXIT_FAILURE);
    }
    if (lockf(pid_fd, F_TLOCK, 0) < 0) {
        /* Can't lock file */
        syslog(LOG_ERR, "Daemon already exists and up!");
        exit(EXIT_FAILURE);
    }
    /* Get current PID */
    sprintf(str, "%d\n", getpid());
    /* Write PID to lockfile */
    write(pid_fd, str, strlen(str));
}

/* Main function */
int main(int argc, char *argv[])
{
    int ret = 0;

    /* It is also possible to use glibc function deamon()
     * at this point, but it is useful to customize your daemon. */
    daemonize();

    /* Open system log and write message to it */
    openlog(argv[0], LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "Started %s", app_name);

    /* Daemon will handle two signals */
    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_signal);

    /* Try to open log file to this daemon */
    log_stream = fopen(log_file_name, "a+");
    if (log_stream == NULL) {
        syslog(LOG_ERR, "Can not open log file: %s, error: %s",
               log_file_name, strerror(errno));
        log_stream = stdout;
    }

    /* This global variable can be changed in function handling signal */
    running = 1;

    /* Never ending loop of server */
    while (running == 1) {
        /* Debug print */
        ret = fprintf(log_stream, "Debug: %d\n", counter++);
        if (ret < 0) {
            syslog(LOG_ERR, "Can not write to log stream: %s, error: %s",
                   (log_stream == stdout) ? "stdout" : log_file_name, strerror(errno));
            break;
        }
        ret = fflush(log_stream);
        if (ret != 0) {
            syslog(LOG_ERR, "Can not fflush() log stream: %s, error: %s",
                   (log_stream == stdout) ? "stdout" : log_file_name, strerror(errno));
            break;
        }

        /* TODO: dome something useful here */

        /* Real server should use select() or poll() for waiting at
         * asynchronous event. Note: sleep() is interrupted, when
         * signal is received. */
        sleep(delay);
    }

    fclose(log_stream);

    /* Write system log and close it. */
    syslog(LOG_INFO, "Stopped %s", app_name);
    closelog();

    /* Free allocated memory */
    if (log_file_name != NULL) free(log_file_name);
    if (pid_file_name != NULL) free(pid_file_name);

    return EXIT_SUCCESS;
}
