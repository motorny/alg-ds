#include "OperationsWithList.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main() {

  List* top = NULL;
  List* input = NULL;
  FILE* file;

  file = fopen("List.txt", "r");
  if (file == NULL) {
    printf("cannot open file");
    return ERROR_OPENING_FILE;
  }

  List* person = NULL;
  char* buffer = (char*)calloc(3 * SIZE, sizeof(char));

  while (!feof(file)) {
    fgets(buffer, 3 * SIZE, file);
    person = TransformToList(buffer);
    AddToList(&top, person);
  }

  PrintList(&top);

  printf("Enter the request in format <<surname>> <<name>> <<second name>> : ");

  fgets(buffer, 3 * SIZE, stdin);
  input = TransformToList(buffer);
  int count = PrintRequest(&top, input);
  if (count == 0) {
    printf("no matches found in list");
  }

  free(input);
  free(buffer);
  FreeList(&top);

  fclose(file);
  return 0;

}