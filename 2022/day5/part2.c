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
    Stack *part2 = NULL;
    size_t len, size;
    bool finished_building_stacks = false;

    // Allocate for the part2 Stack array.
    part2 = malloc(sizeof(Stack) * LEN);
    exit_on_failure(part2, "Failed to build part2 Stack array");

    // Initialize each crate in stack
    for (int i = 0; i < LEN; i++) {
        part2[i].cap = 1; part2[i].len = 0; part2[i].array = NULL;
    }

    stream = fopen(argv[1], "r");
    exit_on_failure(stream, "Failed to open file");
    while ((size = getline(&line, &len, stream)) != - 1) {

        // If the first character in the line is a newline character,
        // stacks have finished being built.
        if (line[0] == '\n') {
            // Flip stack so that the portion being appended is added to the
            // back of the stack and not the front (its easier to append to
            // the end of an array than to the start)
            stackflip(part2, LEN);
            finished_building_stacks = true;
            continue;
        }

        // Build stacks 
        if (!finished_building_stacks) {
            parse_stacks(line, size, part2);
            continue;
        }

        // Handle commands 
        if (finished_building_stacks) {
            // num: Number of crates being moved
            // src: Where the crates are being moved from
            // dest: Where the crates are being moved to
            parse_commands(line, &num, &src, &dest);

            // Append crates in range len(src) to len(src) - num
            // to the destination stack
            stack_append(&part2[dest - 1], &part2[src - 1], num);
            continue;
        }
    }

    // Print stacks and free
    for(int i = 0; i < LEN; i++) {
        putchar(stack_pop(&part2[i]));
        free(part2[i].array);
    }
    putchar('\n');

    free(part2);
    free(line);
    fclose(stream);

    return 0;
}

