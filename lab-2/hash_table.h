#pragma once

#define MSUCCESS 1
#define MFAIL -1
#define ALREADYEXISTS 0

typedef enum {
	FREE,
	FULL,
	DELETED
} status_t;

typedef struct {
	char* str;
	status_t status;
} hash_elem_t;

typedef struct {
	int size;
	hash_elem_t* table;
} hash_table_t;

hash_table_t* hashInit(int hashTSize);
int hashAdd(hash_table_t* h, char elem[]);
hash_elem_t* hashFind(hash_table_t* h, char elem[]);
int hashDelete(hash_table_t* h, char elem[]);
void clear(hash_table_t* h);