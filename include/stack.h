#ifndef STACK
#define STACK
#include <stddef.h>
#include <ctype.h>

/**
 * Simple dynamic stack in C.
 * - **Memory ownership remains with the caller**
 */
typedef struct Stack {
    size_t size;    // current number of elements in the stack
    size_t cap;     // maximum allocated capacity
    void **items;   // array of pointers to objects
} Stack;

Stack *stk_create(size_t cap);
int stk_push(Stack *stack, void *item);
void *stk_pop(Stack *stack);
void stk_free(Stack *stack);

#endif