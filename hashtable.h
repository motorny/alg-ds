#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct elem_t elem_t;
struct elem_t {
  int isDeleted;
  char key[100];
  elem_t* next;
};

typedef struct list_t list_t;
struct list_t {
  elem_t* head;
};

typedef struct hash_table {
  unsigned size;
  list_t* table;
}hash_table;

int insertInList(list_t* list, char* key);
int findInList(list_t* list, char* key);
int deleteInList(list_t* list, char* key);
void clearList(list_t* list);
unsigned hashfunction(char* key, unsigned table_size);
void createHashtable(hash_table* table, unsigned size);
void clearHashtable(hash_table* table);
int insertInHashtable(hash_table* table, char* key);
int deleteInHashtable(hash_table* table, char* key);
int findInHashtable(hash_table* table, char* key);
