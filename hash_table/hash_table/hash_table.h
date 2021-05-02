#pragma once

#define MAX_INPUT_LENGTH 12

typedef struct node{
	node* next;
	char* str;
} node;


typedef struct {
	node** table;
	size_t size;
} hash_table;


int hash_func(const char* str, int table_size);
hash_table* init_table(int size, int str_size);
void insert_node(hash_table* t, node* new_node);
void print_table(hash_table* t);
void free_table(hash_table* t);
void insert_str(hash_table* t,const char* str, int str_len);
node* init_node(const char* str, int str_len);
node* find_node(hash_table* t, const char* str);
bool remove(hash_table* t, const char* str);

