#ifndef STACK
#define STACK
#include <stddef.h>
#include <stdbool.h>

/**
 * Simple dynamic stack in C.
 * - **Memory ownership remains with the caller**
 */
typedef struct Stack {
    size_t size;    // current number of elements in the stack
    size_t cap;     // maximum allocated capacity
    int *items;     // dynamically allocated array of integers
} Stack;

Stack *stk_create(size_t cap);
void stk_free(Stack *stack);
bool stk_empty(const Stack *stack);
int stk_push(Stack *stack, int value);
int stk_top(const Stack *stack);
int stk_pop(Stack *stack);

#endif