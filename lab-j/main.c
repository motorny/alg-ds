#include "hasht.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

void Process(ht_t* ht) {
	char symb, operation, number[1024];
	int index = 0, key;

	symb = getchar();
	while (symb != EOF) {
		operation = symb;
		symb = getchar();

		while (isspace(symb)) {
			symb = getchar();
		}
		while (isdigit(symb)) {
			number[index++] = symb;
			symb = getchar();
		}

		number[index] = '\0';
		//key = atoi(number);
		index = 0;
		switch (operation) {
		case 'a':
			Add(ht, number);
			break;
		case 'r':
			Remove(ht, number);
			break;
		case 'f':
			if (Find(ht, number) == OK)
				printf("yes\n");
			else
				printf("no\n");
			break;
		default:
			printf("Incorrect input");
			return;
		}

		symb = getchar();
		if (symb == '\r')
			symb = getchar();
		if (symb == '\n')
			symb = getchar();
	}
}


int main() {
	ht_t* ht;
	unsigned size = 999983;

	Init(&ht, size);
	Process(ht);
	Delete(&ht);
	return OK;
}