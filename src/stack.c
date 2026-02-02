#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/** Create a new stack with a specific capacity. */
Stack *stk_create(size_t cap){
    if(cap == 0){
        fprintf(stderr, "%s", "stack capacity must be greater than zero.\n");
        return NULL;
    }

    Stack *stack = malloc(sizeof(*stack));
    if(stack == NULL){
        fprintf(stderr, "%s", "stack allocation failed.\n");
        return NULL;
    }

    stack->items = malloc(cap * sizeof(int));
    if(stack->items == NULL){
        fprintf(stderr, "%s", "stack buffer allocation failed.\n");
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->cap = cap;

    return stack;
}

bool stk_empty(const Stack *stack){
    if(stack == NULL){
        return true;
    }
    return stack->size == 0;
}

/**
 * push an item in the stack and increase size.
 * if size equal capacity stack is resized by double of initial capacity
 * - **Memory ownership of item remains with the caller**
 * - stack and item must be non-null
 */
int stk_push(Stack *stack, int item){
    if(stack == NULL){
        fprintf(stderr, "%s", "stack must be non-null.\n");
        return 0;
    }

    if(stack->size == stack->cap){
        size_t new_cap = stack->cap * 2;
        if(new_cap == 0){
            new_cap = 1;
        }
        int *new_items = realloc(stack->items, new_cap * sizeof(int));
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

int stk_top(const Stack *stack){
    if(stack == NULL){
        fprintf(stderr, "%s", "stack must be non-null.\n");
        return 0;
    }
    
    if(stack->size == 0){
        fprintf(stderr, "%s", "stack is empty.\n");
        return 0;
    }

    return stack->items[stack->size-1];
}

/**
 * remove last item in the stack and decrease size.
 * - stack must be non-null
 */
int stk_pop(Stack *stack){
    if(stack == NULL){
        fprintf(stderr, "%s", "stack must be non-null.\n");
        return 0;
    }
    
    if(stack->size == 0){
        fprintf(stderr, "%s", "stack is empty.\n");
        return 0;
    }

    int out = stack->items[--stack->size];
    stack->items[stack->size] = 0;

    return out;
}

/**Memory ownership of items remains with the caller */
void stk_free(Stack *stack){
    if(stack == NULL){
        return;
    }
    free(stack->items);
    free(stack);
}