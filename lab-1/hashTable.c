#include "hashTable.h"
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

enum {
	FREE,
	DELETED,
	BUSY,
} status_t;

hash_t* CreateTable(int size) {
	hash_t* table = (hash_t*)malloc(size * sizeof(hash_t));
	if (table == NULL)
		return NULL;

	for (int i = 0; i < size; i++) {
		table[i].data = NULL;
		table[i].status = FREE;
	}

	return table;
}

static int SimpleHashFunc(int key) {
	return key % NUMBER_M_HASH_1;
}
static int HashFunc(data_t key, int prob) {
	int keyInt = 0;
	int i = 0;

	while (key[i] != 0) {
		keyInt += key[i];
		i++;
	}

	return (int)(SimpleHashFunc(keyInt) + NUMBER_C1_HASH2 * prob + NUMBER_C2_HASH2 * prob * prob) % NUMBER_M_HASH_2;
}

int Add(hash_t* table, const data_t key) {
	for (int prob = 0; prob < TABLE_SIZE; prob++) {
		int index = HashFunc(key, prob);

		if (table[index].status == FREE || table[index].status == DELETED) {
			table[index].data = (data_t)malloc((strlen(key) + 1));
			strcpy(table[index].data, key);
			table[index].status = BUSY;
			return 1;
		}
		else
			if (table[index].status == BUSY && strcmp(table[index].data, key) == 0)
				return 0;
	}
	return 0;
}

int Find(const hash_t* table, const data_t key) {
	for (int prob = 0; prob < TABLE_SIZE; prob++) {
		int index = HashFunc(key, prob);

		if (table[index].status == FREE) {
			return -1;
		}
		else
			if (table[index].status == BUSY && strcmp(table[index].data, key) == 0)
				return index;
	}
	return -1;
}

int Del(hash_t* table, const data_t key) {
	int index = Find(table, key);

	if (index == -1) {
		return 0;
	}
	else {
		table[index].status = DELETED;
	}

	return 0;
}

void Destroy(hash_t* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i].data != NULL)
			free(table[i].data);
	}
	free(table);
}
