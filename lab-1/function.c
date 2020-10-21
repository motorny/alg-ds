#include "Function.h"

word_t* AddItem(word_t* first, char* string, int size) {
  word_t* current = first, *newel = NULL;

  newel = (word_t*)malloc(sizeof(word_t));
  newel->word = string;
  newel->size = size;
  newel->next = NULL;
  if (first == NULL) {
    first = newel;
  }
  else {
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newel;
  }

  return first;
}
///////////////////
//////////////////
word_t* SortWords(word_t* first) {
  word_t* current = first, * next = NULL, * swap = NULL, * prev = NULL;
  check_t check = FACED;
  int i = 0;

  if (first == NULL)
    return NULL;

  while (check == FACED) {
    check = NOTFACED;
    current = first;

    while (current->next != NULL) {
      next = (word_t*)current->next;

      for (i = 0; (i < current->size) && (i < next->size) && (current->word[i] == next->word[i]); i++);

      if (i == (current->size) || (next->word[i] > current->word[i])) {
        prev = current;
        current = next;
        next = (word_t*)next->next;
        continue;
      }
      if ((i == (next->size)) || (next->word[i] < current->word[i])) {
        if (current == first) {
          swap = first;
          first = (word_t*)current->next;
          current->next = next->next;
          next->next = (struct word_t*)swap;
          check = FACED;

          prev = first;
          current = next;
          next = (word_t*)next->next;
          continue;
        }
        swap = (word_t*)prev->next;
        prev->next = current->next;
        current->next = next->next;
        next->next = (struct word_t*)swap;
        check = FACED;

        prev = current;
        current = next;
        next = (word_t*)next->next;
        continue;
      }
    }
  }
  return first;
}
///////////////////
//////////////////
void PrintWords(word_t* first) {
  word_t* current = first;
  int i = 0;
  while (current != NULL) {
    for (i = 0; i < current->size; i++) {
      printf("%c", current->word[i]);
    }
    printf("\n");
    current = (word_t*)current->next;
  }
}
///////////////////
//////////////////
void MemoryFree(word_t* first) {
  word_t* current = first, * next = NULL;

  while (current != NULL) {
    next = (word_t*)current->next;
    free(current);
    current = next;
  }
}