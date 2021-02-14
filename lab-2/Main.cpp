#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "memallocator.h"

typedef struct Head {
	int size;
	int check;
	struct Head* next;
}Head;

int main(void) {
	char ptr[30];
	int whaaat;
	int size = 30 - memgetminimumsize();
	meminit(ptr, 30);
	char* buf = (char*)memalloc(size);
	whaaat = ((Head*)(buf - sizeof(Head)))->check;
	return 0;
}