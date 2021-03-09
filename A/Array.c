#include <stdlib.h>

#include "Array.h"

int* append(int* arr, int* size, int value) {
    if (arr == NULL) {
        arr = (int*) malloc(sizeof(int) * BLOCK);
    }
    if (!(*size % BLOCK) && *size)
        arr = (int*) realloc(arr, sizeof(int) * (*size + BLOCK));
    arr[*size] = value;
    (*size)++;

    return arr;
}

int* popleft(int* arr, int* size) {
    for (int i = 1; i < *size; i++)
        arr[i - 1] = arr[i];
    if (!(--(*size) % BLOCK)) {
        arr = (int*) realloc(arr, sizeof(int*) * (*size));
    }
    return arr;
}

void freeArray(int* arr) {
    free(arr);
}