#include <assert.h>
#include <string.h>
#include "join.h"
int main() {
	struct List list = { NULL,0 };
	struct Data data;
	data = GenerateOne(NULL);
	Add(&list, &data);
	assert(list.size == 1);
	assert(list.first->data.int_field == data.int_field);
	assert(strcmp(data.str_field1, list.first->data.str_field1) == 0);
	assert(strcmp(data.str_field2, list.first->data.str_field2) == 0);
	return 0;
}