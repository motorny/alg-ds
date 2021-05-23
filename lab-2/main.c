#include <stdio.h>
#include "hash_table.h"
#pragma warning(disable: 4996)

int Read(char* data) {
  char ch = (char)getchar();

  if (ch == EOF)
    return 0;

  scanf("%s", data);
  getchar();

  switch (ch) {
  case 'a':
    return 1;
  case 'f':
    return 2;
  case 'r':
    return 3;
  default:
    return 0;
  }
}

int main(void) {
  int var;
  hash_table_t* h = hashInit(100003);
  char data[256];

  var = Read(data);
  while (var) {
    switch (var) {
    case 1:
      hashAdd(h, data);
      break;
    case 2:
      if (hashFind(h, data) != NULL)
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      hashDelete(h, data);
      break;
    }

    var = Read(data);
  }

  clear(h);
  return 0;
} 