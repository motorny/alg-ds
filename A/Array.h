#ifndef ARRAY_H
#define ARRAY_H

#define BLOCK 8

int* append(int* arr, int* size, int value);

int* popleft(int* arr, int* size);

void freeArray(int* arr);

#endif // ARRAY_H