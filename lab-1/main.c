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
	int n = sizeof(s) / maxLength*sizeof(char);
	list_t* list = NULL;
	list = Insert (s, n);
	char* str = Merge(list, n);
	printf("%s", str);
	free(str);
	ListDestroy(list);
	_CrtDumpMemoryLeaks();
	return 0;

}