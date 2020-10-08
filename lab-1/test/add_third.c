#include <assert.h>
#include "join.h"
int main() {
	struct List list = { NULL,0 };
	struct Data data1;
	struct Data data2;
	struct Data data3;
	data1.int_field = 10;
	data2.int_field = 5;
	data3.int_field = 7;
	Add(&list, &data1);
	Add(&list, &data2);
	Add(&list, &data3);
	assert(list.size == 3);
	assert(list.first->data.int_field == 5);
	assert(list.first->next->data.int_field == 7);
	assert(list.first->next->next->data.int_field == 10);
	return 0;
}