#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "scanner.h"
#include "stack.h"
#include "scanner.h" 

int main(void){
    char *re = "ab(cd)";
    printf("%s -> %s\n", re, insert_concatenation(re));

    return 0;
}
