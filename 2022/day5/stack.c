#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


void exit_on_failure(void* ptr, char* string)
{
    if (ptr == NULL) {
        fprintf(stderr, "%s\n", string);
        exit(EXIT_FAILURE);
    }
}


void resize_stack(Stack* stack)
{
    // If the length matches the capcity, increase the capacity by
    // twofold. No need to be considerate of null terminator, as null
    // terminators will not be used.
    if (stack->len >= stack->cap) {
        stack->cap *= 2;
        stack->array = realloc(stack->array, sizeof(char) * stack->cap);
    }
}


void stack_push(Stack* stack, char elem)
{
    // If the array hasn't been created, create the
    // array.
    if (stack->array == NULL) {
        stack->array = malloc(sizeof(char) * stack->cap);
        exit_on_failure(stack->array, "Failed to initialize stack array");
    }

    // Resizes stack if necessary, otherwise does nothing.
    resize_stack(stack);

    stack->array[stack->len] = elem;
    stack->len++;
}


char stack_pop(Stack* stack)
{
    char returned;
    stack->len--;
    return stack->array[stack->len];
}


void stack_print(Stack* stack)
{
    for (int i = 0; i < stack->len; i++)
        printf("%c", stack->array[i]);
    putchar('\n');
}


void stack_reverse_portion(Stack* stack, int len)
{
    char temp; 
    int start = stack->len - len;

    // Bitwise swap
    for (int i = 0; i < len / 2; i++) {
        stack->array[start + i] ^= stack->array[start + len - i - 1];
        stack->array[start + len - i - 1] ^= stack->array[start + i];
        stack->array[start + i] ^= stack->array[start + len - i - 1];
    }
    /*
    // Ordinary swap
    for (int i = 0; i < len / 2; i++) {
        temp = stack->array[start + i];
        stack->array[start + i] = stack->array[start + len - i - 1];
        stack->array[start + len - i - 1] = temp;
    }
    */
}


void stackflip(Stack* stacks, int rows)
{
    int index = 0;
    for (int i = 0; i < rows; i++) {
        stack_reverse_portion(&stacks[i], stacks[i].len);
        index = 0;
    }
}


void stackcopy(Stack* dest, Stack* src, uint32_t len)
{
    for (int i = 0; i < len; i++) {
        dest[i].len = src[i].len;
        dest[i].cap = src[i].cap;
        dest[i].array = malloc(sizeof(char) * dest[i].cap);
        exit_on_failure(dest, "Failed to allocate for copy stack when copying");
        for (int j = 0; j < dest[i].len; j++)
            dest[i].array[j] = src[i].array[j];
    }
}


void stack_append(Stack* dest, Stack* src, int num)
{
    char *dest_ptr;
    char *src_ptr;

    // Reallocate to make room for appended stack
    dest->len += num;
    if (dest->len >= dest->cap) {
        while (dest->len >= dest->cap)
            dest->cap *= 2;
        dest->array = realloc(dest->array, sizeof(char) * dest->cap);
        exit_on_failure(dest->array, "Failed to reallocate in extension");
    }

    dest_ptr = &dest->array[dest->len - num];
    src_ptr = src->array + (src->len - num);

    memcpy(dest_ptr, src_ptr, num);
    src->len -= num;
}


void stack_swap(Stack* dest1, Stack* src1, Stack* dest2, Stack* src2, int num)
{
    char *swap1, *swap2;

    // Logic here is that both need to be the same length
    swap1 = malloc(sizeof(char) * (dest1->len + num));
    swap2 = malloc(sizeof(char) * (dest1->len + num)); 

    // Deal with right facing side
    memcpy(swap1, dest1->array, dest1->len);
    memcpy(swap1 + dest1->len, src1->array, num);

    // Deal with left facing side
    memcpy(swap2, &src2->array[src2->len - num], num);
    memcpy(swap2 + num, dest2->array, dest2->len);

    // Finalize lengths for first
    dest1->len += num;
    free(dest1->array);
    dest1->array = swap1; 
    memmove(src1->array, src1->array + num, src1->len - num);
    src1->len -= num;

    // Finalize lengths for second
    src2->len -= num;
    dest2->len += num;
    free(dest2->array);
    dest2->array = swap2;
}


