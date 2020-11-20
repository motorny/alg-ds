#include<stdio.h>
#include"list.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include<assert.h>
#include<string.h>
#pragma warning(disable:4996)


int main(void) {
	char s[][maxLength]  = {"lpl", " ghtyghtdgd"};
	int n = sizeof(s) / maxLength * sizeof(char);
	int len = Length(s, n);
	list_t* list = NULL;
	list = InsertTextToList (s, n);
	char* str = Merge(list, len);
	printf("%s", str);
	free(str);
	ListDestroy(list);
	_CrtDumpMemoryLeaks();
	return 0;

}
