/*
 * Author: Schuyler Kelly
 * Date: 6 December 2022
 */
#include "stack.h"

// Converts quickly from a string to an int.
int fast_atoi(char*);

// Parses commands into the command array passed.
void parse_commands(char* line, int* num, int* src, int* dest);

void parse_stacks(char* line, int llen, Stack* stack);

