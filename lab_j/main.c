#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"


int main() {
	int tableSize = 100000;
	hash_t* table = InitTable(tableSize);
	int strSize;
	char action;
	char* str = (char*)malloc(MAX_LENGTH * sizeof(char));
	if (!str)
		return;
	while (1) {
		action = getchar();
		if (action == EOF || action == '\n')
			break;

		getchar();
		fgets(str, MAX_LENGTH, stdin);
		strSize = strlen(str);
		str[strSize - 1] = '\0';

		if (action == 'a')
			Insert(table, str, strSize);
		else if (action == 'r')
			Remove(table, str);
		else if (action == 'f') {
			if (Find(table, str) != NULL)
				printf("yes\n");
			else
				printf("no\n");
		}
	}
	DestroyTable(table);
	return 0;
}