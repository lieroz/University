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

#define INIT_VEC_SIZE 8
#define VEC_MULT 3
#define BUFFER_SIZE 1024

typedef struct dirent dirent_t;
typedef struct stat stat_t;

typedef struct vector {
    unsigned count;
    unsigned capacity;
    void **data;
} vector_t;

vector_t *new_vector()
{
    vector_t *vec = (vector_t *) malloc(sizeof(vector_t));
    if (vec == NULL) return NULL;

    vec->data = (void **) malloc(INIT_VEC_SIZE * sizeof(void *));
    if (vec->data == NULL) return NULL;

    vec->count = 0;
    vec->capacity = INIT_VEC_SIZE;

    return vec;
}

void delete_vector(vector_t **vec)
{
    if (vec == NULL) return;

    free((*vec)->data);
    (*vec)->count = (*vec)->capacity = 0;
    free(*vec);
}

void push(vector_t *vec, void *arg)
{
    if (vec->count == vec->capacity) {
        vec->capacity *= VEC_MULT;
        void **tmp = (void **) realloc(vec->data, vec->capacity * sizeof(void *));

        if (tmp == NULL) {
            return;
        } else {
            vec->data = tmp;
        }
    }

    vec->data[vec->count++] = arg;
}

void *pop(vector_t *vec)
{
    void *result = vec->data[--vec->count];
    return result;
}

void sort_vector(vector_t *vec, int (*cmpfunc)(const void *, const void *))
{
    qsort(vec->data, vec->count, sizeof(void *), cmpfunc);
}

int dirent_cmp_func(const void *_a, const void *_b)
{
    dirent_t *a = *(dirent_t **) _a;
    dirent_t *b = *(dirent_t **) _b;
    return strcmp(a->d_name, b->d_name) > 0;
}

int recursive_walker(const char *dir_name, const char *fmt, bool print_files)
{
    DIR *dir;
    vector_t *vec = new_vector();
    dirent_t *entry;
    stat_t st;
    const char *indent = "├── ";

    if (!(dir = opendir(dir_name))) {
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
        }

        push(vec, entry);
    }

    sort_vector(vec, dirent_cmp_func);

    for (unsigned i = 0; i < vec->count; ++i) {
        entry = (dirent_t *) vec->data[i];
        char path[BUFFER_SIZE];
        char format[BUFFER_SIZE];

        if (i == vec->count - 1) {
            indent = "└── ";
            snprintf(format, sizeof(format), "%s%*s", fmt, 4, "");
        } else {
            snprintf(format, sizeof(format), "%s│%*s", fmt, 3, "");
        }


        if (entry->d_type == DT_DIR) {
            printf("%s%s%s%s%s\n", fmt, indent, BOLDBLUE, entry->d_name, RESET);
            chdir(entry->d_name);
            getcwd(path, BUFFER_SIZE);
            recursive_walker(path, format, print_files);
        }

        if (entry->d_type != DT_DIR && print_files) {
            getcwd(path, BUFFER_SIZE);
            lstat(path, &st);
            printf("%s%s%s (%s%ld b%s)\n", fmt, indent, entry->d_name, BOLDGREEN, st.st_size, RESET);
        }
    }

    chdir("..");
    delete_vector(&vec);
    closedir(dir);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        recursive_walker(".", "", false);
    } else if (argc == 2) {
        if (strcmp(argv[1], "-f") == 0) {
            recursive_walker(".", "", true);
        } else {
            if (recursive_walker(argv[1], "", false) != 0) {
                fprintf(stderr, "Directory not found!\n");
            }
        }
    } else if (argc == 3) {
        if (strcmp(argv[2], "-f") == 0) {
            if (recursive_walker(argv[1], "", true) != 0) {
                fprintf(stderr, "Directory not found!\n");
            }
        } else {
            fprintf(stderr, "Unknown argument: [%s]\n", argv[2]);
        }
    } else {
        fprintf(stderr, "Invalid amount of arguments!\n");
    }

    return 0;
}
