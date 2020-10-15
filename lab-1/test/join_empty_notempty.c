#include <assert.h>
#include "join.h"
#include "create_test_list.h"
CR
int main() {
	struct List list1  = { NULL,0 }; 
	struct List* list2 = CreateTestList(5, 7, 10);
	struct List list3;
	list3 = Join(&list1, list2);
	assert(list3.size == 3);
	assert(list3.first->data.int_field == 5);
	assert(list3.first->next->data.int_field == 7);
	assert(list3.first->next->next->data.int_field == 10);
	return 0;
}
