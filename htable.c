#include"htable.h"
#include<stdlib.h>
#include<string.h>
#pragma warning(disable: 4996)

htable* hInit(int hSize) {
	htable* table = (htable*)malloc(sizeof(htable) * hSize);
	if (!table) {
		return NULL;
	}
	for (int i = 0; i < hSize; i++) {
		table[i].status = FREE;
	}
	return table;
}

int hFunc(char* str, int size) {
	int sum = 0;
	for (int i = 0; str[i] != 0; i++) {
		sum += str[i];
	}
	return sum % size;
}

int hAdd(htable* h, char elem[], int hSize) {
	int pos0 = hFunc(elem, hSize), pos = pos0, respos = -1, i = 0;

	do {
		if (h[pos].status == NOTFREE && strcmp(h[pos].str, elem) == 0)
			return FAIL;

		if (h[pos].status == FREE || h[pos].status == DELETED) {
			respos = pos;
			break;
		}
		i++;
		pos = (pos0 + i * K) % hSize;
	} while (pos != pos0);
	if (respos != -1) {
		h[respos].str = malloc((strlen(elem) + 1) * sizeof(char));
		strcpy(h[respos].str, elem);
		h[respos].status = NOTFREE;
		return SUCCESS;
	}
	return FAIL;
}

int hFind(htable* h, char elem[], int hSize) {
	int pos0 = hFunc(elem, hSize), pos = pos0, i = 0;
	do {
		if (h[pos].status == FREE) {
			return FAIL;
		}
		if (h[pos].status == NOTFREE && strcmp(h[pos].str, elem) == 0)
			return SUCCESS;
		i++;
		pos = (pos0 + i * K) % hSize;
	} while (pos != pos0);
	return FAIL;
}

int hDelete(htable* h, char elem[], int hSize) {
	int pos0 = hFunc(elem, hSize), pos = pos0, i = 0;
	do {
		if (h[pos].status == FREE) {
			return FAIL;
		}
		if (h[pos].status == NOTFREE && strcmp(h[pos].str, elem) == 0) {
			free(h[pos].str);
			h[pos].status = DELETED;
			return SUCCESS;
		}
		i++;
		pos = (pos0 + i * K) % hSize;
	} while (pos != pos0);
	return FAIL;
}