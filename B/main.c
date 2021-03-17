#include <stdio.h>

#include "memallocator.h"

int main() {

    int size = 2000;
    char c[size];
    int res = meminit(c, size);
    printf("%d", res);
    memdone();
    return 0;
}
