#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

void listdir(const char *name, const char *fmt, bool print_files)
{
    DIR *dir;
    struct dirent *entry, *last_entry;
    struct stat st;
    const char *indent = "├── ";

    if (!(dir = opendir(name))) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        last_entry = entry;
    }

    rewinddir(dir);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[strlen(name) + strlen(entry->d_name) + 3];
        char format[strlen(fmt) + 7];

        if (entry == last_entry) {
            indent = "└── ";
            snprintf(format, sizeof(format), "%s%*s", fmt, 4, "");
        } else {
            snprintf(format, sizeof(format), "%s│%*s", fmt, 3, "");
        }

        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

        if (entry->d_type == DT_DIR) {
            printf("%s%s%s%s%s\n", fmt, indent, BOLDBLUE, entry->d_name, RESET);
            listdir(path, format, print_files);
        }

        if (entry->d_type != DT_DIR && print_files) {
            stat(path, &st);
            printf("%s%s%s (%s%ld b%s)\n", fmt, indent, entry->d_name, BOLDGREEN, st.st_size, RESET);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Invalid amount of arguments!");
        return 1;
    }

    bool print_files = argc == 3 ? strcmp(argv[2], "-f") == 0 : false;
    listdir(argv[1], "", print_files);

    return 0;
}

