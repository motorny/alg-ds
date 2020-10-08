#ifndef MERGELISTS_H_INCLUDED__
#define MERGELISTS_H_INCLUDED__

#pragma once

// Two following structures form a "notebook" structure:
// list_t - list for first letters, which also contain a pointer to sublist
// sublist_t - list for words starting with this letter
typedef struct subList_t {
  char* word;
  struct subList_t* next;
} subList_t;

typedef struct list_t {
  char letter;
  subList_t* words;
  struct list_t* next;
} list_t;

list_t* CreateList(int* err);

void DestroyList(list_t* p);

subList_t* FindPlaceForWord(char* newWord, list_t* p, int* err);

subList_t* AddWord(char* newWord, list_t* p, int* err);

list_t* AddLetter(char newLetter, list_t* p, int* err);

list_t* FindLetterMatch(list_t* list, char letter, int* flagMatchFound, int* err);

list_t* MergeLists(list_t* list1, list_t* list2, int* err);

#endif
