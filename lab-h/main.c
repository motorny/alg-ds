#include "aatree.h"
#include <ctype.h>
#pragma warning(disable: 4996)

void Process(aatree_t* tree){
	char symb, operation, number[1024];
	int index = 0, key;

	symb = getchar();
	while (symb != EOF){
		operation = symb;
		symb = getchar();

		while (isspace(symb)){
			symb = getchar();
		}
		while (isdigit(symb)){
			number[index++] = symb;
			symb = getchar();
		}

		number[index] = '\0';
		key = atoi(number);
		index = 0;
		switch (operation){
		case 'a':
			Add(tree, key);
			break;
		case 'r':
			Remove(tree, key);
			break;
		case 'f':
      if (Search(tree, key) == FOUND)
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      printf("Incorrect input");
      return;
    }

    symb = getchar();
    if (symb == '\r')
      symb = getchar();
    if (symb == '\n')
      symb = getchar();
	}
}


int main() {
  aatree_t* tree = Create();
	Process(tree);
  Delete(tree);
  return OK;
}