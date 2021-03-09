#ifndef ARRAY_H
#define ARRAY_H

#define BLOCK 8

#include <stdlib.h>

#include "Array.h"

int* append(int* arr, int* size, int value);

int* popleft(int* arr, int* size);

void freeArray(int* arr);

#endif // ARRAY_H