/*
 * Author: Schuyler Kelly
 * Date: 6 December 2022
 * Purpose: Read file into stacks.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "parser.h"
#define LEN 9


int fast_atoi(char* string)
{
    int value = 0;
    while (*string)
        value = value * 10 + (*string++ - '0');
    return value;
}


void parse_commands(char* line, int* num, int* src, int* dest)
{
    uint32_t i = 0;
    char *token = NULL;
    line[strcspn(line, "\n")] = ' ';
    token = strtok(line, " ");
    while(token != NULL) {
        switch(i) {
            case 1:
                *num = fast_atoi(token);
                break;
            case 3:
                *src = fast_atoi(token);
                break;
            case 5:
                *dest = fast_atoi(token);
                break;
        }
        token = strtok(NULL, " ");
        i++;
    }
}


void parse_stacks(char* line, int llen, Stack* stack)
{
    uint32_t ind = 0;
    for (int i = 0; i < llen - 1; i++) {
        if ((i - 1) % 4 == 0) {
            if (line[i] >= 'A' && line[i] <= 'Z')
                stack_push(&stack[ind], line[i]);
        ind++;
        }
    }
}


