#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "scanner.h" 

/// @brief Apply the thompson transformation.
/// @param input the regex
/// @return the related NFA.
TNode *thompson(char *input){
    Stack op_stack;
}