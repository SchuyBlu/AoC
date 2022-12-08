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


uint32_t analyze_plot(char **plot, size_t nrowsl, size_t row_len)
{
    bool visible_in_column, visible_in_row;
    bool visible_on_left, visible_on_right;
    bool visible_on_top, visible_on_bottom;
    uint32_t count = 0;

    // Go through each character
    for (int i = 1; i < nrowsl - 1; i++) {
        for (int j = 1; j < row_len - 1; j++) {
            // Add to count for every tree on outside of the
            // plot
            //if ((i == 0) || (i == nrowsl - 1)) {
            //    count++;
            //    continue;
            //}
            // Reset boolean values
            visible_on_left = true;
            visible_on_right = true;
            visible_on_top = true;
            visible_on_bottom = true;
            visible_in_column = true;
            visible_in_row = true;

            // Character is at plot[i][j]
            // Now check character against all four directions
            // Check each column first
            for (int k = 0; k < row_len; k++) {
                // If k is bigger than j and still visible
                // in column, break because its visible from
                // one side
                if ((k > j) && visible_on_left) break;

                // If checking against itself, ignore
                if (j == k) continue;

                // Checking left side. If current num is bigger than
                // num being analyzed, set left bool to false
                if ((k < j) && plot[i][k] >= plot[i][j])
                    visible_on_left = false;

                // Check right side using same logic as above
                if ((k > j) && plot[i][k] >= plot[i][j])
                    visible_on_right = false;

                // If neither visible on left or visible on right,
                // visible in column is not true
                if ((!visible_on_left) && (!visible_on_right))
                    visible_in_column = false;

                // If not visible in column, break to prevent unecessary
                // iteration
                if (!visible_in_column)
                    break;
            }

            // Now check each row
            for (int l = 0; l < nrowsl; l++) {
                // If l is bigger than i and still visible on top,
                // break because its visible on one side.
                if ((l > i) && visible_on_top) break;

                // If checking against itself, ignore
                if (i == l) continue;

                // Checking top side. If current num is bigger than
                // num being analyzed, set the top bool to false
                if ((l < i) && plot[l][j] >= plot[i][j])
                    visible_on_top = false;

                // Check bottom side using the same logic as above
                if ((l > i) && plot[l][j] >= plot[i][j])
                    visible_on_bottom = false;

                // If neither visible on top or visible on bottom,
                // visible in row is not true
                if ((!visible_on_top) && (!visible_on_bottom))
                    visible_in_row = false;

                // If not visible in row, break to prevent unecessary
                // iteration
                if (!visible_in_row)
                    break;
            }

            // Now that both rows and columns have been checked, if either is true
            // we can add one to the count
            if (visible_in_row || visible_in_column) {
                count++;
            }
        }
    }
    return count;
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

