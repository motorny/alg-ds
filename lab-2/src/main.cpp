
#include "malloc.h"
#include "memallocator.h"

int main() {
 void *p1 = 0, *p2 = 0;
 int  memsize = memgetminimumsize() + memgetblocksize() + 2;
 void *ptr = malloc(memsize);
 meminit(ptr, memsize);
 p1 = memalloc(1); // Success!
 p2 = memalloc(1); // Success!
 memfree(p2);
 memfree(p1);
 memdone();
 free(ptr);
    return 0;
}
