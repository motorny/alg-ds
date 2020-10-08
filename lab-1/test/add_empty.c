#include <assert.h>
#include "join.h"
int main() {
	struct List list = { NULL,0 };
	Add(&list, NULL);
	assert(list.size == 0);
	return 0;
}