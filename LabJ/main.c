#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "hash_table.h"

int main() {
	const uint size = 10000;
	hashTable_t* hashTable = CreateTable(size);
	char c = getchar();
	int number = 0;

	while (c != EOF) {
		scanf("%d", &number);
		switch (c) {
		case 'a':
			AddInTable(hashTable, number);
			break;
		case 'r':
			RemoveFromTable(hashTable, number);
			break;
		case 'f':
			if (FindInTable(hashTable, number))
				printf("yes\n");
			else
				printf("no\n");
			break;
		default:
			printf("Incorrect input");
			return 0;
		}

		c = getchar();
		if (c == '\r')
			c = getchar();
		if (c == '\n')
			c = getchar();
	}
	return 0;
}