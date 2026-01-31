#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "scanner.h"
#include "stack.h"
#include "scanner.h" 

int main(void){
    TNode *node = malloc(sizeof(*node));
    node->state = 1;

    Stack *stack = stk_create(10);
    stk_push(stack, node);

    TNode *out;
    out = stk_pop(stack);
    printf("%d\n", out->state);

    return 0;
}
