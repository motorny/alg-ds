#include"HashTable.h"

table_t* CreateHash() {

  table_t* table;

  table = (table_t*)malloc(sizeof(table_t) * SIZE);
  if (table == NULL)
    return NULL;

  for (int i = 0; i < SIZE; i++)
    table[i].state = DELETED;

  return table;

}

static int HashFunc(char* str) {

  int index = 0;

  for (int i = 0; str[i] != 0; i++)
    index += str[i];

  return index % SIZE;

}

int Add(table_t* table, char* str) {
  int pos0 = HashFunc(str);
  int pos = pos0, respos = -1, i = 0;
  do {
    if (table[pos].state == NOTFREE && strcmp(table[pos].str, str) == 0)
      return FALSE;

    if (table[pos].state == FREE || table[pos].state == DELETED) {
      respos = pos;
      break;
    }

    i++;
    pos = (pos0 + i * 1) % SIZE;
  } while (pos != pos0);

  if (respos != -1) {
    table[respos].str = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(table[respos].str, str);
    table[respos].state = NOTFREE;
    return TRUE;
  }

  return FALSE;
}

int Find(table_t* hashT, char* str) {
  int pos0 = HashFunc(str), pos = pos0, i = 0;

  do {
    if (hashT[pos].state == FREE) {
      return FALSE;
    }
    if (hashT[pos].state == NOTFREE && strcmp(hashT[pos].str, str) == 0)
      return TRUE;

    i++;
    pos = (pos0 + i * 1) % SIZE;
  } while (pos != pos0);

  return FALSE;
}

int Delete(table_t* hashT, char* str) {
  int p0 = HashFunc(str), pos = p0, i = 0;

  do {
    if (hashT[pos].state == FREE) {
      return FALSE;
    }

    if (hashT[pos].state == NOTFREE && strcmp(hashT[pos].str, str) == 0) {
      free(hashT[pos].str);
      hashT[pos].state = DELETED;
      return TRUE;
    }

    i++;
    pos = (p0 + i * 1) % SIZE;
  } while (pos != p0);

  return FALSE;
}

void hashDestroy(table_t* table) {

  for (int i = 0; i < SIZE; i++)
    if (table[i].state == NOTFREE)
      free(table[i].str);
  free(table);

}