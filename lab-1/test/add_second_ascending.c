#include <assert.h>
#include "join.h"
int main() {
	struct List list = { NULL,0 };
	struct Data data1;
	struct Data data2;
	data1.int_field = 5;
	data2.int_field = 10;
	Add(&list, &data1);
	Add(&list, &data2);
	assert(list.size == 2);
	assert(list.first->data.int_field == 5);
	assert(list.first->next->data.int_field == 10);
	return 0;
}