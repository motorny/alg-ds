#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "join.h"
int main() {
	FILE* f = fopen("test.bin", "wb");
	WriteToFile(f, 20);
	fflush(f);
	fseek(f, 0, SEEK_END);
	assert(ftell(f) == 20 * sizeof(struct Data));
	fclose(f);
	system("del test.bin");
	return 0;
}