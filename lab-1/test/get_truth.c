#include <assert.h>
#include <string.h>
#include "join.h"
int main() {
	struct List list = { NULL,0 };
	struct Data data1;
	struct Data data2;
	struct Data data3;
	data1.int_field = 5;
	data2.int_field = 7;
	data3.int_field = 10;
	Add(&list, &data1);
	Add(&list, &data2);
	Add(&list, &data3);
	assert(Get(&list, 0).int_field == 5);
	assert(Get(&list, 1).int_field == 7);
	assert(Get(&list, 2).int_field == 10);
	return 0;
}