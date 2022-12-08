#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


void exit_on_failure(void *ptr, char *message)
{
    if (ptr == NULL) {
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}


void print_plot(char **plot, size_t nrowsl, size_t row_len)
{
    for (int i = 0; i < nrowsl; i++) {
        for (int j = 0; j < row_len; j++)
            putchar(plot[i][j]);
        putchar('\n');
    }
}


char** build_plot(FILE *stream, char **plot, size_t *nrowsl, size_t *nrowsc, size_t *row_len)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    while ((nread = getline(&line, &len, stream)) != -1) {
        if (plot == NULL) {
            // Allocate for row position
            // Stripping the null terminator and newline character, as
            // I don't want a string, just a 2D char array with characters
            // from 0 to 9
            *row_len = nread - 1;
            plot = malloc(sizeof(char*) * *nrowsc);
            exit_on_failure(plot, "Failed to allocate for rows");

            // Allocate for row itself
            plot[*nrowsl] = malloc(sizeof(char) * *row_len);
            exit_on_failure(plot[*nrowsl], "Failed to allocate for a row"); 
        }
        else {
            // Grow plot if necessary
            if (*nrowsl >= *nrowsc) {
                *nrowsc *= 2;
                plot = realloc(plot, sizeof(char*) * *nrowsc);
                exit_on_failure(plot, "Failed to reallocate for rows");
            }
            // Allocate for row itself
            plot[*nrowsl] = malloc(sizeof(char) * *row_len);
            exit_on_failure(plot[*nrowsl], "Failed reto allocate for a row");
        }
        // Fill row
        memcpy(plot[*nrowsl], line, *row_len); 
        (*nrowsl)++;
    }
    return plot;
}


int analyze_plot(char **plot, size_t nrowsl, size_t row_len)
{
    int temp_count;
    int lcount, rcount, tcount, bcount, scenic_score = 0;

    // Go through each character
    for (int i = 0; i < nrowsl; i++) {
        for (int j = 0; j < row_len; j++) {
            // Look in the left direction
            temp_count = 0;
            for (int k = j - 1; k >= 0; k--) {
                if (!(plot[i][k] < plot[i][j])) {
                    temp_count++;
                    break;
                }
                temp_count++;
            }
            lcount = temp_count;
            temp_count = 0;

            // Look in the right direction
            for (int k = j + 1; k < row_len; k++) {
                if (!(plot[i][k] < plot[i][j])) {
                    temp_count++;
                    break;
                }
                temp_count++;
            }
            rcount = temp_count;
            temp_count = 0;

            // Look from the top
            for (int k = i - 1; k >= 0; k--) {
                if (!(plot[k][j] < plot[i][j])) {
                    temp_count++;
                    break;
                }
                temp_count++;
            }
            tcount = temp_count;
            temp_count = 0;

            // Look from bottom
            for (int k = i + 1; k < nrowsl; k++) {
                if (!(plot[k][j] < plot[i][j])) {
                    temp_count++;
                    break;
                }
                temp_count++;
            }
            bcount = temp_count;
            temp_count = 0;

            // Check if scenic score gets overwritten
            if (scenic_score <= (lcount * rcount * tcount * bcount))
                scenic_score = lcount * rcount * tcount * bcount;
        } 
    }
    return scenic_score;
}


int main(int argc, char **argv)
{
    // File declarations
    FILE *stream = NULL;

    // 2D array declarations
    char **plot = NULL;
    size_t nrowsl = 0, nrowsc = 1;
    size_t row_len;

    // Declaration for plot analyzation
    uint32_t trees_that_are_visible;

    stream = fopen(argv[1], "r");
    exit_on_failure(stream, "Failed to open file");
 
    // Build the plot
    plot = build_plot(stream, plot, &nrowsl, &nrowsc, &row_len);

    // Analyze the plot
    trees_that_are_visible = analyze_plot(plot, nrowsl, row_len);
    printf("%d\n", trees_that_are_visible);

    return 0;
}

