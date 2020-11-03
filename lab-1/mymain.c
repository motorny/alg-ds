#include "concat_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int main(void) {
	int len = 0;
	list_t list;

	error_t error = NO_ERRORS;
	char* result = NULL;
	char buff[10] = "hello!\0";

	list.head = NULL;
	list.tail = NULL;

	CreateList(&list, &len, &error);
	result = Concat(&list, &len, &error);
	DestoyList(&list, &error);

	printf("%s", result);

	free(result);

	return 0;
}

