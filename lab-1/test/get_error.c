#include <assert.h>
#include <string.h>
#include "join.h"
int main() {
	struct List list = { NULL,0 };
	assert(strcmp(Get(&list, 5).str_field1, "Error") == 0);
	return 0;
}