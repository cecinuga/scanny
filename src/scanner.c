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

static TNode *make_fragment(char token){
    TNode *init_state = malloc(sizeof(*init_state));
    TNode *acc_state = malloc(sizeof(*acc_state));

    init_state->state = 0;
    init_state->token = token;
    init_state->to = acc_state;
    acc_state->state = 1;

    return init_state;
}

void apply_operator(Stack *stack, char op){
    switch (op)
    {
    case '.':
        
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
TNode *thompson(char *input){
    Stack *op_stack = stk_create(50);
    Stack *frag_stack = stk_create(50);
    char *extended_input = insert_concatenation(input);

    int i = 0;
    while(extended_input[i]){
        char token = extended_input[i];
        if(token == '('){
            push_token(op_stack, token);
        } 
        else if (token == ')'){
            while (top_token(op_stack) != '('){
                apply_operator(frag_stack, pop_token(op_stack));
            }
            pop_token(op_stack); // remove '('
        }
        else if(is_literal(token)){
            
            
        }
    }
}
