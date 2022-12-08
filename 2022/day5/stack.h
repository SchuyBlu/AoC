#include <stdint.h>

// Represents a stack, specifically meant to be used
// for day five in Advent of Code.
//
// The stack is simply a char array, with relevant 
// functions for popping and pushing.
//
// capacity - uint32_t - stores the capacity of the
//                       stack
// length   - uint32_t - stores the length of the stack
// array    - char*    - Stores the stack
typedef struct {
    uint32_t cap;
    uint32_t len;
    char *array;
} Stack;


// Method for pushing stack objects
void stack_push(Stack* stack, char elem);

// Method for popping off the last element of 
// the stack.
char stack_pop(Stack* stack);

// Method for printing the stack.
void stack_print(Stack* stack);

// Exits if a failure occurs.
void exit_on_failure(void* ptr, char* string);

// Resizes stack by doubling the capcity if
// the capcity has been reached.
//void resize_stack(Stack* stack);

// Flips a portion of the stack
void stack_reverse_portion(Stack* stack, int len);

// Flips the stack
void stackflip(Stack* stacks, int rows);

// Copy one stack from another stack
void stackcopy(Stack* dest, Stack* src, uint32_t len);

// Append one array to the other
void stack_append(Stack* dest, Stack* src, int num);

void stack_swap(Stack* dest1, Stack* src1, Stack* dest2, Stack* src2, int num);

