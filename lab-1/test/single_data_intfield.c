#include <assert.h>
#include <string.h>
#include "join.h"
int main() {
	struct Data data = GenerateOne(NULL);
	assert(data.int_field >= 0);
	assert(strlen(data.str_field1) < SIZE);
	assert(strlen(data.str_field2) < SIZE);
	assert(32 <= data.str_field1[0] && data.str_field1[0] <= 126);
	assert(32 <= data.str_field2[0] && data.str_field2[0] <= 126);
	return 0;
}
