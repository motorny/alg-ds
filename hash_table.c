#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

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

int HashFunc(const char* str, int tableSize) {
	int hash = 0, i = 0;
	while (str[i]) {
		hash += str[i];
		i++;
	}
	return hash % tableSize;
}

hash_table_t* InitTable(int size) {
	int i;
	hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));
	if (!table)
		return NULL;

	table->size = size;
	table->body = (node_t**)malloc(size * sizeof(node_t*));
	if (!table->body) {
		free(table);
		return NULL;
	}
	for (i = 0; i < size; i++)
		table->body[i] = NULL;

	return table;
}

node_t* FindElem(hash_table_t* table, const char* str) {
	int key;
	node_t* ptrOnCurNode;

	if (!table)
		return NULL;

	key = HashFunc(str, table->size);
	if (!(table->body[key]))
		return NULL;
	ptrOnCurNode = table->body[key];
	while (ptrOnCurNode) {
		if (strcmp(ptrOnCurNode->data, str) == 0)
			return ptrOnCurNode;
		ptrOnCurNode = ptrOnCurNode->next;
	}
	return NULL;
}

int InsertElem(hash_table_t* table, const char* str, int strSize) {
	int key;
	node_t* ptrOnCurNode, * newNode;

	if (!table)
		return T_FAIL;
	newNode = CreateNode(str, strSize);
	if (!newNode)
		return T_FAIL;

	if (FindElem(table, newNode->data) != NULL)
		return T_FAIL;

	key = HashFunc(newNode->data, table->size);
	if (table->body[key] == NULL)
		table->body[key] = newNode;
	else {
		ptrOnCurNode = table->body[key];
		while (ptrOnCurNode->next)
			ptrOnCurNode = ptrOnCurNode->next;
		ptrOnCurNode->next = newNode;
	}
	return T_SUCCESS;
}

int RemoveElem(hash_table_t* table, const char* str) {
	int key;
	node_t* ptrOnCurNode, * ptrOnPrevNode;

	if (!table)
		return T_FAIL;

	key = HashFunc(str, table->size);
	if (!(table->body[key]))
		return T_FAIL;

	ptrOnCurNode = table->body[key];
	ptrOnPrevNode = NULL;
	while (ptrOnCurNode) {
		if (strcmp(ptrOnCurNode->data, str) == 0) {
			if (!ptrOnPrevNode)
				table->body[key] = ptrOnCurNode->next;
			else
				ptrOnPrevNode->next = ptrOnCurNode->next;
			free(ptrOnCurNode->data);
			free(ptrOnCurNode);
			return T_SUCCESS;
		}
		ptrOnPrevNode = ptrOnCurNode;
		ptrOnCurNode = ptrOnCurNode->next;
	}
	return T_FAIL;
}

void DestroyTable(hash_table_t* table) {
	int i;
	node_t* ptrOnCurNode;

	if (!table || !table->body)
		return;

	for (i = 0; i < table->size; i++) {
		if (table->body[i]) {
			ptrOnCurNode = table->body[i];
			while (ptrOnCurNode) {
				table->body[i] = table->body[i]->next;
				free(ptrOnCurNode->data);
				free(ptrOnCurNode);
				ptrOnCurNode = table->body[i];
			}
		}
	}
	free(table->body);
	free(table);
}

void ManageTree(hash_table_t* table) {
	int strSize;
	char action;
	char* str = (char*)malloc(MAX_INPUT * sizeof(char));
	if (!str)
		return;
	while (1) {
		action = getchar();
		if (action == EOF || action == '\n')
			break;

		getchar();
		fgets(str, MAX_INPUT, stdin);
		strSize = strlen(str);
		str[strSize - 1] = '\0';

		if (action == 'a')
			InsertElem(table, str, strSize);
		else if (action == 'r')
			RemoveElem(table, str);
		else if (action == 'f') {
			if (FindElem(table, str) != NULL)
				printf("yes\n");
			else
				printf("no\n");
		}
	}
}

int main() {
	int tableSize = 100000;
	hash_table_t* table = InitTable(tableSize);
	ManageTree(table);
	DestroyTable(table);
	return 0;
}