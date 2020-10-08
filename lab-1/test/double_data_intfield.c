#include <assert.h>
#include <stddef.h>
#include "join.h"
int main() {
	struct Data data1;
	struct Data data = GenerateOne(NULL);
	data1 = GenerateOne(&data);
	assert(data1.int_field >= data.int_field);
	return 0;
}