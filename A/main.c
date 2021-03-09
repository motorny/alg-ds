#include <stdio.h>

#include "List.h"
#include "Array.h"

int main() {

    int* arr = NULL;
    int size = 0;

    arr = append(arr, &size, 1);
    arr = popleft(arr, &size);
    arr = append(arr, &size, 2);
    arr = append(arr, &size, 3);
    arr = append(arr, &size, 4);
    arr = append(arr, &size, 5);
    arr = append(arr, &size, 6);
    arr = append(arr, &size, 7);
    arr = append(arr, &size, 8);
    arr = append(arr, &size, 9);
    arr = append(arr, &size, 10);

    arr = popleft(arr, &size);
    arr = popleft(arr, &size);
    arr = popleft(arr, &size);
    freeArray(arr);

    Node_t* last = NULL;

    last = insert(last, 1);
    last = insert(last, 2);
    last = pop(last);
    last = insert(last, 3);


    freeList(last);

    return 0;
}