#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0

struct HASH_LIST;

typedef struct
{
  unsigned Size;
  struct HASH_LIST* Data;
} HASH_TABLE;

HASH_TABLE* HashTableCreate(int size);
void HashTableClear(HASH_TABLE* tmp);
void HashTableAdd(HASH_TABLE* tmp, char *Data);
void HashTableDelete(HASH_TABLE* tmp, char* Data);
int HashTableFind(HASH_TABLE* tmp, char* Data);

unsigned HashFunction(HASH_TABLE* tmp, char *data);

#endif // HASH_TABLE_H_
