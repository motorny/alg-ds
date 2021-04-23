#ifndef HASH_TABLE_LIST_H
#define HASH_TABLE_LIST_H

#define STRING_MAX_SIZE 300

typedef struct HASH_LIST_ELEMENT HASH_LIST_ELEMENT;
struct HASH_LIST_ELEMENT
{
  char Data[STRING_MAX_SIZE];
  int IsDeleted;
  HASH_LIST_ELEMENT* Next;
};

typedef struct HASH_LIST
{
  HASH_LIST_ELEMENT* Root;
} HASH_LIST;

void HashListAdd(HASH_LIST* L, char *Data);
int HashListFind(HASH_LIST* L, char *Data);
int HashListDelete(HASH_LIST* L, char *Data);
void HashListClear(HASH_LIST* L);

#endif // ! 
