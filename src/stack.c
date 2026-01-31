#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include "stack.h"

/** Create a new stack with a specific capacity. */
Stack *stk_create(size_t cap){
    Stack *stack = malloc(sizeof(*stack));
    stack->size = 0;
    stack->cap = cap;
    stack->items = calloc(cap, sizeof(void*));

    return stack;
}

/**
 * push an item in the stack and increase size.
 * if size equal capacity stack is resized by double of initial capacity
 * - **Memory ownership of item remains with the caller**
 * - stack and item must be non-null
 */
int stk_push(Stack *stack, void *item){
    if(stack == NULL){
        fprintf(stderr, "%s", "stack must be non-null.\n");
        return 0;
    }
    if(item == NULL){
        fprintf(stderr, "%s", "item must be non-null.\n");
        return 0;
    }
    
    if(stack->size == stack->cap){
        int new_cap = stack->cap*2;
        void **new_items = realloc(stack->items, new_cap*sizeof(void*));
        if(new_items == NULL){
            fprintf(stderr, "%s", "stack resizing failed.\n");
            return 0;
        }

        stack->items = new_items;
        stack->cap = new_cap;
    }

    stack->items[stack->size++] = item;

    return 1;
}

/**
 * remove last item in the stack and decrease size.
 * - stack must be non-null
 */
void *stk_pop(Stack *stack){
    if(stack == NULL){
        fprintf(stderr, "%s", "stack must be non-null.\n");
        return 0;
    }
    
    if(stack->size == 0){
        fprintf(stderr, "%s", "stack is empty.\n");
        return 0;
    }

    void *out = stack->items[--stack->size];
    stack->items[stack->size] = NULL;

    return out;
}

/**Memory ownership of items remains with the caller */
void stk_free(Stack *stack){
    if(stack == NULL){
        fprintf(stderr, "%s", "stack must be non-null.\n");
        return 0;
    }
    free(stack->items);
    free(stack);
}