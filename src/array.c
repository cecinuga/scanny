#include "array.h"
#include <stdlib.h>
#include <stdio.h>

Array *arr_create(int capacity){
    if(capacity == 0){
        fprintf(stderr, "%s", "stack capacity must be greater than zero.\n");
        return NULL;
    }
    Array *array = malloc(sizeof(Array));
    if(array == NULL){
        printf("[!] Error no more memory allocating array-");
        return NULL;
    }
    array->items = malloc(sizeof(void*)*capacity);
    if(array->items == NULL){
        printf("[!] Error no more memory allocating array.");
        free(array);
        return NULL;
    }
    array->length = 0;
    array->capacity = capacity;

    return array;
}

void *arr_get(Array *array, unsigned const i){
    if(array == NULL){
        printf("[!] array must be non-null");
        return NULL;
    }
    if(array->items == NULL){
        printf("[!] array items must be non-null");
    }
    if(i > array->length){
        printf("[!] index must be less than length");
    }

    return array->items[i];
}

int arr_push(Array *array, void *item){
    if(array == NULL){
        printf("[!] array must be non-null");
        return NULL;
    }
    if(item == NULL){
        printf("[!] item must be non-null");
        return NULL;
    }
    if(array->length == array->capacity){
        size_t new_cap = array->capacity * 2;
        if(new_cap == 0){
            new_cap = 1;
        }
        int *new_items = realloc(array->items, new_cap * sizeof(int));
        if(new_items == NULL){
            fprintf(stderr, "%s", "array resizing failed.\n");
            return 0;
        }

        array->items = new_items;
        array->capacity = new_cap;
    }

    array->length++;
    array->items[array->length] = item;
    
}