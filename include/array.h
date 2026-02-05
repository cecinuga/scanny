#ifndef ARRAY
#define ARRAY

typedef struct Array {
    size_t length;
    size_t capacity;
    void **items;
} Array;

Array *arr_create(size_t capacity);
void *arr_get(Array *array, unsigned const i);
int arr_push(Array *array, void *item);

#endif