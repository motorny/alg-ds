#include <assert.h>
#include "join.h"
#include "create_test_list.h"
CR
int main() {
	struct List* list1 = CreateTestList(5, 7, 9);
	struct List* list2 = CreateTestList(10, 11, 15);
	struct List list3;
	list3 = Join(list1, list2);
	assert(list3.size == 6);
	assert(Get(&list3, 0).int_field == 5);
	assert(Get(&list3, 1).int_field == 7);
	assert(Get(&list3, 2).int_field == 9);
	assert(Get(&list3, 3).int_field == 10);
	assert(Get(&list3, 4).int_field == 11);
	assert(Get(&list3, 5).int_field == 15);
	return 0;
}
