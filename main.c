#define _CRT_SECURE_NO_WARNINGS

#include "HashTable.h"
#pragma warning(disable:4996)


int main(void) {

  table_t* tab = CreateHash();
  int size = 1000;
  char c = getchar(), str[SIZE], command;
  while (c != EOF) {
    int i = 0;
    command = c;
    c = getchar();
    while (isspace(c))
    {
      c = getchar();
    }
    while (isdigit(c)) {
      str[i++] = c;
      c = getchar();
    }
    str[i] = '\0';
    if (command == 'a') {
      Add(tab, str);
    }
    else if (command == 'r') {
      Delete(tab, str);
    }
    else if (command == 'f') {
      if (Find(tab, str) == TRUE)
        printf("yes\n");
      else
        printf("no\n");
    }
    else {
      continue;
    }
    if (c == '\r' || c == '\n')
      c = getchar();
  }
  return 0;
}