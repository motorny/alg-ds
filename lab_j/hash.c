#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

#pragma warning(disable: 4996)

node_t* CreateNode(const char* str, int strSize) {
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (!newNode)
		return NULL;
	newNode->data = (char*)malloc(sizeof(char) * strSize);
	if (!(newNode->data)) {
		free(newNode);
		return NULL;
	}
	strcpy_s(newNode->data, strSize, str);
	newNode->next = NULL;
	return newNode;
}

int Hash(const char* str, int tableSize) {
	int hash = 0, i = 0;
	while (str[i]) {
		hash += str[i];
		i++;
	}
	return hash % tableSize;
}

hash_t* InitTable(int size) {
	int i;
	hash_t* table = (hash_t*)malloc(sizeof(hash_t));
	if (!table)
		return NULL;

	table->size = size;
	table->body = (node_t * *)malloc(size * sizeof(node_t*));
	if (!table->body) {
		free(table);
		return NULL;
	}
	for (i = 0; i < size; i++)
		table->body[i] = NULL;

	return table;
}

node_t* Find(hash_t* table, const char* str) {
	int key;
	node_t* currNode;

	if (!table)
		return NULL;

	key = Hash(str, table->size);
	if (!(table->body[key]))
		return NULL;
	currNode = table->body[key];
	while (currNode) {
		if (strcmp(currNode->data, str) == 0)
			return currNode;
		currNode = currNode->next;
	}
	return NULL;
}

int Insert(hash_t* table, const char* str, int strSize) {
	int key;
	node_t* currNode;
	node_t* newNode;

	if (!table)
		return FALSE;
	newNode = CreateNode(str, strSize);
	if (!newNode)
		return FALSE;

	if (Find(table, newNode->data) != NULL)
		return FALSE;

	key = Hash(newNode->data, table->size);
	if (table->body[key] == NULL)
		table->body[key] = newNode;
	else {
		currNode = table->body[key];
		while (currNode->next)
			currNode = currNode->next;
		currNode->next = newNode;
	}
	return TRUE;
}

int Remove(hash_t* table, const char* str) {
	int key;
	node_t* currNode;
	node_t* prevNode;

	if (!table)
		return FALSE;

	key = Hash(str, table->size);
	if (!(table->body[key]))
		return FALSE;

	currNode = table->body[key];
	prevNode = NULL;
	while (currNode) {
		if (strcmp(currNode->data, str) == 0) {
			if (!prevNode)
				table->body[key] = currNode->next;
			else
				prevNode->next = currNode->next;
			free(currNode->data);
			free(currNode);
			return TRUE;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}
	return FALSE;
}

void DestroyTable(hash_t* table) {
	int i;
	node_t* currNode;

	if (!table || !table->body)
		return;

	for (i = 0; i < table->size; i++) {
		if (table->body[i]) {
			currNode = table->body[i];
			while (currNode) {
				table->body[i] = table->body[i]->next;
				free(currNode->data);
				free(currNode);
				currNode = table->body[i];
			}
		}
	}
	free(table->body);
	free(table);
}
