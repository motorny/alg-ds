#include <assert.h>
#include "join.h"
int main() {
	struct List list1 = { NULL,0 };
	struct List list2 = { NULL,0 };
	struct List list3;
	struct Data data1;
	struct Data data2;
	struct Data data3;
	data1.int_field = 5;
	data2.int_field = 7;
	data3.int_field = 10;
	Add(&list1, &data1);
	Add(&list1, &data2);
	Add(&list1, &data3);
	data1.int_field = 4;
	data2.int_field = 6;
	data3.int_field = 8;
	Add(&list2, &data1);
	Add(&list2, &data2);
	Add(&list2, &data3);
	list3 = Join(&list1, &list2);
	assert(list3.size == 6);
	assert(Get(&list3, 0).int_field == 4);
	assert(Get(&list3, 1).int_field == 5);
	assert(Get(&list3, 2).int_field == 6);
	assert(Get(&list3, 3).int_field == 7);
	assert(Get(&list3, 4).int_field == 8);
	assert(Get(&list3, 5).int_field == 10);
	return 0;
}