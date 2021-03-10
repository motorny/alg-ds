#include <stdlib.h>

#include "Array.h"

int* append(int* arr, int* size, int value) {
    if (!(*size % BLOCK))
        arr = (int*) realloc(arr, sizeof(int) * (*size + BLOCK));
    if (arr == NULL)
        return NULL;
    arr[(*size)++] = value;
    return arr;
}

int* popleft(int* arr, int* size) {
    for (int i = 1; i < *size; i++)
        arr[i - 1] = arr[i];
    if (!(--(*size) % BLOCK))
        // if `realloc` fails, `arr` is NULL == no need to explicitly check
        arr = (int*) realloc(arr, sizeof(int*) * (*size));
    return arr;
}

void freeArray(int* arr) {
    free(arr);
}