#pragma warning (disable: 4996)
#include"hash.h"

#include<string.h>

hashTable_t* hashCreate(int size) {

  hashTable_t* hashTable;
  
  hashTable = (hashTable_t*)malloc(sizeof(hashTable_t) * size);
  if (hashTable == NULL)
    return NULL;

  for (int i = 0; i < size; i++)
    hashTable[i].status = DELETED;

  return hashTable;

}

//hash function 
static int hashFunction(char* str, int size) {

  int index = 0;

  for (int i = 0; str[i] != 0; i++)
    index += str[i];

  return index % size;

}
//insert
void hashInsert(hashTable_t* hashTable, char* elem, int size) {

  int key = hashFunction(elem, size);
  int index = key;
  for(int pos = 0; pos < size; pos++){
    if (hashTable[index].status == FREE || hashTable[index].status == DELETED) {
      hashTable[index].str = (char*)malloc((strlen(elem) + 1) * sizeof(char));
      strcpy(hashTable[index].str, elem);
      hashTable[index].status = NOTFREE;
      return;
    }
    else
      if (hashTable[index].status == NOTFREE && strcmp(hashTable[index].str, elem) == 0)
        return;
    index = (key + pos + 1) % size;
  }
}
//find
int hashFind(hashTable_t* hashTable, char* elem, int size) {

  int key = hashFunction(elem, size);
  int index = key;
  for (int pos = 0; pos < size; pos++) {
    if (hashTable[index].status == NOTFREE && strcmp(hashTable[index].str, elem) == 0)
      return FOUND;
    else
      if (hashTable[index].status == DELETED)
        return NOTFOUND;
    index = (key + pos + 1) % size;
  }

  return NOTFOUND;

}
//delete
void hashDelete(hashTable_t* hashTable,char* elem, int size) {

  int key = hashFunction(elem, size);
  int index = key;
  for (int pos = 0; pos < size; pos++) {
    if (hashTable[index].status == NOTFREE && strcmp(hashTable[index].str, elem) == 0){
      free(hashTable[index].str);
      hashTable[index].status = FREE;
      return;
    }
    else
      if(hashTable[index].status == DELETED)
        return;
    index = (key + pos + 1) % size;
  }

}

void hashDestroy(hashTable_t* hashTable, int size) {

  for (int i = 0; i < size; i++)
    if(hashTable[i].status == NOTFREE)
      free(hashTable[i].str);
  free(hashTable);

}