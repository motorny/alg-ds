#pragma once

#define MAX_LENGTH 20

typedef enum {
	FALSE = 0,
	TRUE = 1,
}bool_t;

typedef struct node_t {
	char* data;
	struct node_t* next;
} node_t;

typedef struct hash_t {
	node_t** body;
	int size;
} hash_t;


hash_t* InitTable(int size);
int Insert(hash_t* table, const char* str, int strSize);
int Remove(hash_t* table, const char* str);
node_t* Find(hash_t* table, const char* str);
void DestroyTable(hash_t* table);