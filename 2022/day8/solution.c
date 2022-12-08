#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef struct {
    uint32_t cap;
    uint32_t len;
    char *row;
} DimensionalArray;


void exit_on_failure(void *ptr, char *message)
{
    if (ptr == NULL) {
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}


void resize(void *ptr, size_t *cap, size_t *len, size_t size)
{
    if (ptr == NULL) {
        ptr = malloc(size * *cap);
        exit_on_failure(ptr, "Failed to allocate memory");
    }
    else {
        if (*cap <= *len) {
            (*cap) *= 2;
            ptr = realloc(ptr, size);
            exit_on_failure(ptr, "Failed to reallocate memory");
        }
    }
}


int main(int argc, char **argv)
{
    FILE *stream = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    size_t arrcap = 1;
    size_t arrlen = 0;
    DimensionalArray *column = NULL;

    stream = fopen(argv[1], "r");
    exit_on_failure(stream, "Failed to open file");

    resize(column, &arrcap, &arrlen, sizeof(DimensionalArray));
    
    while ((nread = getline(&line, &len, stream)) != -1) {
        printf("%s", line);
    }

    free(column);

    return 0;
}

