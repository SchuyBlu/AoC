#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char** argv)
{
    // Part 1 declarations
    uint32_t total = 0;
    bool not_found;

    // Part 2 declarations
    uint32_t badges = 0, line_num = 0, lnum[3];
    char *tline[3];
    //char *line1 = NULL, *line2 = NULL, *line3 = NULL;

    // Necessary for both 1 and 2
    FILE *fptr;
    char *line = NULL;
    size_t len = 0, size = 0;

    // Open file
    fptr = fopen("input", "r");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to open\n");
        exit(EXIT_FAILURE);
    }


    //tline = malloc(sizeof(char**) * 3);
    size = getline(&line, &len, fptr);
    while (size != -1) {
        line[size - 1] = '\0';

        // Part 1
        not_found = true;
        for (int i= 0; i < (size - 1) / 2; i++) {
            for (int j = (size - 1) / 2; j < size - 1; j++) {
                if (line[i] == line[j] && not_found) {
                    if (line[i] >= 'A' && line[i] < 'a')
                        total += (line[i] - 'A') + 27;
                    else if (line[i] >= 'a')
                        total += (line[i] - 'a') + 1;
                    not_found = false;
                }
            }
        }

        // Part 2
        if (line_num == 2) {
            tline[line_num] = malloc(sizeof(char) * size);
            strcpy(tline[line_num], line);
            lnum[line_num] = size;
            not_found = true;
            for (int i = 0; i < lnum[0]; i++) {
                for (int j = 0; j < lnum[1]; j++) {
                    for (int n = 0; n < lnum[2]; n++) {
                        if (tline[0][i] == tline[1][j] && tline[0][i] == tline[2][n] && not_found) {
                            if (tline[0][i] >= 'A' && tline[0][i] < 'a')
                                badges += (tline[0][i] - 'A') + 27;
                            else if (tline[0][i] >= 'a')
                                badges += (tline[0][i] - 'a') + 1;
                            not_found = false;
                        }
                    }
                }
            }
            line_num = -1;
            free(tline[0]);
            free(tline[1]);
            free(tline[2]);
        }
        else {
            tline[line_num] = malloc(sizeof(char) * size); 
            strcpy(tline[line_num], line);
            lnum[line_num] = size;
        }
        size = getline(&line, &len, fptr);
        line_num++;
    }
    free(line);
    fclose(fptr);
    printf("Part 1: %d\nPart 2: %d\n", total, badges);
    return 0;
}

