#include "Hash.h"


int hashFunc(int size, char* str, int index)
{
	int key = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		key += str[i];
	}

	return (key % size + index + 7) % size;
}

HashTable* createHashTable(int size)
{
	HashTable* table = malloc(sizeof(HashTable));
	if (table == NULL)
	{
		return NULL;
	}

	table->size = size;
	table->data = malloc(sizeof(Cell) * size);
	if (table->data == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < size; i++)
	{
		table->data[i].status = FREE;
	}

	return table;
}

void add(HashTable* table, char* str)
{
	int index;

	for (int i = 0; i < table->size; i++)
	{
		index = hashFunc(table->size, str, i);

		if (table->data[index].status == FREE || table->data[index].status == DELETED)
		{
			table->data[index].str = malloc(sizeof(char) * strlen(str));
			if (table->data[index].str == NULL)
			{
				return;
			}
			strcpy(table->data[index].str, str);
			table->data[index].status = NOT_FREE;
			return;
		}
		if (table->data[index].status == NOT_FREE && strcmp(table->data[index].str, str) == 0)
		{
			return;
		}
	}
}

void del(HashTable* table, char* str)
{
	int index;

	for (int i = 0; i < table->size; i++)
	{
		index = hashFunc(table->size, str, i);

		if (table->data[index].status == FREE)
		{
			return;
		}
		if (table->data[index].status == NOT_FREE && strcmp(table->data[index].str, str) == 0)
		{
			free(table->data[index].str);
			table->data[index].status = DELETED;
			return;
		}
	}
}

int find(HashTable* table, char* str)
{
	int index;

	for (int i = 0; i < table->size; i++)
	{
		index = hashFunc(table->size, str, i);

		if (table->data[index].status == FREE)
		{
			return NOT_FOUND;
		}
		if (table->data[index].status == NOT_FREE && strcmp(table->data[index].str, str) == 0)
		{
			return FOUND;
		}
	}
}
