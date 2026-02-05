#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "scanner.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_literal(char c) {
    return isalnum(c);  // estendibile
}

static int can_end_expr(char c) {
    return is_literal(c) || c == ')' || c == '*';
}

static int can_start_expr(char c) {
    return is_literal(c) || c == '(';
}

static char *insert_concatenation(const char *re) {
    size_t len = strlen(re);
    // worst case: every char needs a '.'
    char *out = malloc(2 * len + 1);
    if (!out) return NULL;

    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        char curr = re[i];
        out[j++] = curr;

        if (i + 1 < len) {
            char next = re[i + 1];

            if (can_end_expr(curr) && can_start_expr(next)) {
                out[j++] = '.';
            }
        }
    }

    out[j] = '\0';
    return out;
}

static char top_token(Stack *stack){
    if(stack == NULL){
        printf("[!] Error stack must be non-null");
    }
    return (char)stk_top(stack);
}


static char pop_token(Stack *stack){
    if(stack == NULL){
        printf("[!] Error stack must be non-null");
    }
    return (char)stk_pop(stack);
}

static int push_frag(Stack *stack, Fragment *frag){
    if(stack == NULL){
        printf("[!] Error stack must be non-null");
    }
    return stk_push(stack, frag);
}

static Fragment *pop_frag(Stack *stack){
    if(stack == NULL){
        printf("[!] Error stack must be non-null");
    }
    return (Fragment*)stk_pop(stack);
}

int new_state(){

}

static void apply_operator(Stack *stack, char op){
    if(stack == NULL){
        printf("[!] Error stack must be non-null");
    }
    switch (op)
    {
    case '.':
        /* code */
        break;
    
    case '|':
        /* code */
        break;

    case '*':
        /* code */
        break;
    }
}

/// @brief Apply the thompson transformation.
/// @param input the regex
/// @return the related NFA.
int thompson(char *input){
    Stack *op_stack = stk_create(50);
    Stack *frag_stack = stk_create(50);

    char *extended_input = insert_concatenation(input);

    int i = 0;
    while(extended_input[i]){
        char token = extended_input[i];
        
        i++;
    }

    return 0;
}
