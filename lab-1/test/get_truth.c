#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "join.h"
#include "create_test_list.h"
CR
int main() {
  struct List* li = CreateTestList(5, 7, 10);
  assert(Get(li, 0).int_field == 5);
  assert(Get(li, 1).int_field == 7);
  assert(Get(li, 2).int_field == 10);
	return 0;
}
