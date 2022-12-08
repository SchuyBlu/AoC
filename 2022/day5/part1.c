#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "parser.h"
#define LEN 9

int main(int argc, char** argv)
{
    FILE *stream = NULL;
    char *line = NULL;
    int num, dest, src;
    Stack *stacks = NULL, *ghosts = NULL;
    size_t len, size;
    bool finished_building_stacks = false;

    // Allocate for the stack array.
    stacks = malloc(sizeof(Stack) * LEN);
    exit_on_failure(stacks, "Failed to build Stack array");

    // Allocate for the ghost stack array.
    ghosts = malloc(sizeof(Stack) * LEN);
    exit_on_failure(ghosts, "Failed to build ghost Stack array");

    for (int i = 0; i < LEN; i++) {
        stacks[i].cap = 1; stacks[i].len = 0; stacks[i].array = NULL;
        ghosts[i].cap = 1; ghosts[i].len = 0; ghosts[i].array = NULL;
    }

    stream = fopen(argv[1], "r");
    exit_on_failure(stream, "Failed to open file");
    while ((size = getline(&line, &len, stream)) != - 1) {

        // If the first character in the line is a newline character,
        // stacks have finished being built.
        if (line[0] == '\n') {
            stackcopy(ghosts, stacks, LEN);

            // Flip the stacks. This is so that the portion pushed later
            // is appended to the end of each stack, not the front (PART 2)
            // and is so that ghosts and stacks are facing different
            // directions (PART 1)
            stackflip(stacks, LEN);
            finished_building_stacks = true;
            continue;
        }

        // Build stacks if empty line hasn't been reached
        if (!finished_building_stacks) {
            parse_stacks(line, size, stacks);
            continue;
        }

        // Handle commands if stacks are built
        if (finished_building_stacks) {
            // num: number of crates being moved
            // src: where the crates are moved from
            // dest: where the crates are moved to
            parse_commands(line, &num, &src, &dest);
            stack_swap(&stacks[dest - 1], &ghosts[src - 1], &ghosts[dest - 1], &stacks[src - 1], num);
            continue;
        }
    }

    // Printing and freeing stacks
    for (int i = 0; i < LEN; i++) {
        putchar(stack_pop(&stacks[i]));
        free(stacks[i].array);
        free(ghosts[i].array);
    }
    putchar('\n');

    free(stacks);
    free(ghosts);
    free(line);
    fclose(stream);

    return 0;
}

