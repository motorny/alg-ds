#pragma once

#define T_FAIL 0
#define T_SUCCESS 1

#define MAX_INPUT 20

typedef struct node_t {
	char* data;
	struct node_t* next;
} node_t;

typedef struct hash_table_t {
	node_t** body;
	int size;
} hash_table_t;


hash_table_t* InitTable(int size);
int InsertElem(hash_table_t* table, const char* str, int strSize);
int RemoveElem(hash_table_t* table, const char* str);
node_t* FindElem(hash_table_t* table, const char* str);
void DestroyTable(hash_table_t* table);
