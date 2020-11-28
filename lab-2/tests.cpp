#include <stdio.h>
#include <cstdlib>
#include "memallocator.h"
//#include "memalloc.c"

int main(void) {

	void* p = 0;
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	p = memalloc(1); // Success!
	memfree(p);
	memdone();

	free(ptr);

	void* p1 = 0, * p2 = 0;
	int  memsize = memgetminimumsize() + memgetblocksize() + 2;
	void* ptr2 = malloc(memsize);
	meminit(ptr2, memsize);
	p1 = memalloc(1); // Success!
	p2 = memalloc(1); // Success!
	memfree(p2);
	memfree(p1);
	memdone();
	free(ptr2);




	return 0;
}