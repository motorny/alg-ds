#include<stdio.h>
#include<stdlib.h>
#include "funcs.h"
#pragma warning(disable : 4996)


int main(void) {
	int key;
	treap* t = NULL;
	int operation = getchar();
	while (operation != EOF) {
		scanf("%i", &key);
		if (operation == 'a')
			Add(&t, key);
		else if (operation == 'r')
			Delete(&t, key);
		else if (operation == 'f')
			if (Find(t, key) == FOUND)
				printf("yes\n");
			else printf("no\n");
		else {
			TreapOff(t);
			return 0;
		}
		operation = getchar();
		if (operation == '\n')
			operation = getchar();
	}
	TreapOff(t);
	return 0;
}