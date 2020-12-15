#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "memallocator.h"

int main(void) {
    const int memBlockSize1 = 7500 * sizeof(void*), memBlockSize2 = 75000 * sizeof(void*);
    int i;
    void* ptr = malloc(memBlockSize1);
    static void* allocated[10000];
    LARGE_INTEGER t1, t2, freq;

    meminit(ptr, memBlockSize1);

    printf("TEST: 500 allocations, free 1/3 of it, allocate back, 500 allocations more, free 1000\n");

    QueryPerformanceFrequency(&freq);

    srand(30);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < 500; i++)
        allocated[i] = memalloc(rand() % 20 + 1);
    for (i = 0; i < 500; i += 3)
        memfree(allocated[i]);
    for (i = 0; i < 500; i += 3)
        allocated[i] = memalloc(rand() % 20 + 1);
    for (i = 500; i < 1000; i++)
        allocated[i] = memalloc(rand() % 20 + 1);
    for (i = 0; i < 1000; i++)
        memfree(allocated[i]);

    QueryPerformanceCounter(&t2);
    printf("Custom(list) memory manager:  %f\n", (double)(t2.QuadPart - t1.QuadPart) / freq.QuadPart);

    memdone();
    free(ptr);

    srand(30);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < 500; i++)
        allocated[i] = malloc(rand() % 20 + 1);
    for (i = 0; i < 500; i += 3)
        free(allocated[i]);
    for (i = 0; i < 500; i += 3)
        allocated[i] = malloc(rand() % 20 + 1);
    for (i = 500; i < 1000; i++)
        allocated[i] = malloc(rand() % 20 + 1);
    for (i = 0; i < 1000; i++)
        free(allocated[i]);

    QueryPerformanceCounter(&t2);
    printf("Default(malloc/free) memory manager: %f\n", (double)(t2.QuadPart - t1.QuadPart) / freq.QuadPart);

    ptr = malloc(memBlockSize2);
    meminit(ptr, memBlockSize2);

    printf("\nTEST: 5000 allocations, free 1/3 of it, allocate back, 5000 allocations more, free 10000\n");

    QueryPerformanceFrequency(&freq);

    
    QueryPerformanceCounter(&t1);
    for (i = 0; i < 5000; i++)
        allocated[i] = memalloc(rand() % 20 + 1);
    for (i = 0; i < 5000; i += 3)
        memfree(allocated[i]);
    for (i = 0; i < 5000; i += 3)
        allocated[i] = memalloc(rand() % 20 + 1);
    for (i = 5000; i < 10000; i++)
        allocated[i] = memalloc(rand() % 20 + 1);
    for (i = 0; i < 10000; i++)
        memfree(allocated[i]);

    QueryPerformanceCounter(&t2);
    printf("Custom(list) memory manager:  %f\n", (double)(t2.QuadPart - t1.QuadPart) / freq.QuadPart);

    memdone();
    free(ptr);

    srand(59);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < 5000; i++)
        allocated[i] = malloc(rand() % 20 + 1);
    for (i = 0; i < 5000; i += 3)
        free(allocated[i]);
    for (i = 0; i < 5000; i += 3)
        allocated[i] = malloc(rand() % 20 + 1);
    for (i = 5000; i < 10000; i++)
        allocated[i] = malloc(rand() % 20 + 1);
    for (i = 0; i < 10000; i++)
        free(allocated[i]);

    QueryPerformanceCounter(&t2);
    printf("Default(malloc/free) memory manager: %f\n", (double)(t2.QuadPart - t1.QuadPart) / freq.QuadPart);

    return 0;
}