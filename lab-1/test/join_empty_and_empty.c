#include <assert.h>
#include "join.h"
int main() {
	struct List list1 = { NULL,0 };
	struct List list2 = { NULL,0 };
	struct List list3;
	list3 = Join(&list1, &list2);
	assert(list3.size == 0);
	assert(list3.first == NULL);
	return 0;
}