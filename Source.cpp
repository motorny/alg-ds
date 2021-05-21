#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#pragma warning(disable:4996)

typedef struct Cell Cell;
struct Cell {
  char str[200];
  int isFilled;
};

#define SUCCESS 1
#define FAIL 0

int InitTable(Cell** Table, int TableSize) {
  *Table = (Cell*)malloc(sizeof(Cell) * TableSize);

  if (*Table == NULL)
    return FAIL;

  for (int i = 0; i < TableSize; i++)
    (*Table)[i].isFilled = 0;

  return SUCCESS;
}

unsigned  HashFunc1(char* str, int size) {
  int key = 0;

  for (int i = 0; i < strlen(str); i++)
  {
    key += str[i];
  }

  return (key % size  + 7) % size;
}

unsigned HashFunc2(char* str, int size) {
  unsigned result = 0;

  for (int i = 0; str[i] != 0; i++) {
    result += ((unsigned)str[i] + 17)%size;
  }

  return result;
}

int Insert(Cell* ht, int tableSize, char* str) {
  unsigned  index1, index2;

  if (strlen(str) > 200)
    return FAIL;

  index1 = HashFunc1(str, tableSize);
  index2 = HashFunc2(str, tableSize);

  for (int i = 0; i < tableSize; i++) {
    if (ht[index1].isFilled == 0) {
      strcpy(ht[index1].str, str);
      ht[index1].isFilled = 1;
      return SUCCESS;
    }
    else if (ht[index1].isFilled == 1 && strcmp(ht[index1].str, str) == 0)
      return FAIL;
    else
      index1 = (index1 + index2) % tableSize;
  }
  return FAIL;
}

int Search(Cell* table, int tableSize, char* str) {
  unsigned int index1, index2;

  if (strlen(str) > 200)
    return FAIL;

  index1 = HashFunc1(str, tableSize);
  index2 = HashFunc2(str, tableSize);

  for (int i = 0; i < tableSize; i++) {
    if (table[index1].isFilled == 1 && strcmp(table[index1].str, str) == 0)
      return SUCCESS;
    else if (table[index1].isFilled == 0)
      return FAIL;

    index1 = (index1 + index2) % tableSize;
  }
  return FAIL;
}

int Delete(Cell* table, int tableSize, char* str) {
  unsigned index1, index2;

  if (strlen(str) > 100)
    return FAIL;

  index1 = HashFunc1(str, tableSize), index2 = HashFunc2(str, tableSize);
  for (int i = 0; i < tableSize; i++) {
    if (table[index1].isFilled == 1 && strcmp(table[index1].str, str) == 0) {
      table[index1].isFilled = 2;
      return SUCCESS;
    }
    else if (table[index1].isFilled == 0)
      return FAIL;

    index1 = (index1 + index2) % tableSize;
  }
  return FAIL;
}

int main(void)
{
  Cell* table;
  int tableSize = 100000;
  InitTable(&table, tableSize);
  int command;
  char key[200];

  command = getchar();
  while (command != EOF)
  {
    scanf("%s", &key);
    switch (command)
    {
    case 'a':
      Insert(table, tableSize, key);
      break;
    case 'f':
      if (Search(table, tableSize, key))
        printf("yes\n");
      else
        printf("no\n");
      break;
    case 'r':
      Delete(table, tableSize, key);
      break;
    default:
      return 0;
    }
    command = getchar();
    if (command == '\n')
      command = getchar();
  }
  return 0;
}
