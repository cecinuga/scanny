#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "scanner.h"
#include "stack.h"
#include "scanner.h" 

int main(void){
    char *re = "ab(cd)";
    thompson(re);

    return 0;
}
