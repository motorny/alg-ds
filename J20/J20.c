#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "J20.h"

#pragma warning (disable:4996)

#define STR_MUL 10

static int _ind(char* str) {
  int i, ind = 0;

  for (i = 0; str[i] != 0; i++)
    ind += str[i];

  return ind % N;
}

// return 1 && destList == NULL => key is in table by index = destInd
// return 1 && destList != NULL => key is in list by index = destInd and after node = destList
// return 0 && destList == NULL => key is in not found
int FindElem(htable_t ht[], char* str, int* destInd, list_t** destList) {
  int i = _ind(str);

  *destInd = i;

  if (ht[i].num == 0)
    return 0;

  if (strcmp(ht[i].str, str) == 0)
    return 1;

  *destList = ht[i].list;

  if ((*destList) != NULL) {
    list_t *destListNext = (*destList)->next;
    while (destListNext != NULL) {
      if (strcmp(destListNext->str, str) == 0)
        return 1;
      else {
        *destList = (*destList)->next;
        destListNext = destListNext->next;
      }
    }
  }

  return 0;
}

void AddElem(htable_t ht[], char* strNew) {
  int i;
  list_t* list = NULL;

  if (!FindElem(ht, strNew, &i, &list)) {
    if (ht[i].num == 0) {
      ht[i].str = strNew;
      ht[i].num++;
    }
    else {
      list_t* listNew = (list_t*)malloc(sizeof(list_t));
      if (listNew == NULL)
        return;
      if (ht[i].list == NULL) {
        list_t* dummy = (list_t*)malloc(sizeof(list_t));
        if (dummy == NULL)
          return;
        ht[i].list = ht[i].end = dummy;
      }
      listNew->str = strNew;
      listNew->next = NULL;
      ht[i].end->next = listNew;
      ht[i].end = listNew;
      ht[i].num++;
    }
  }
}

void DelElem(htable_t ht[], char* strDel) {
  int i;
  list_t* listPrev = NULL;

  if (FindElem(ht, strDel, &i, &listPrev)) {
    if (listPrev == NULL) {
      ht[i].str = "";
      ht[i].num--;
    }
    else {
      list_t* listToDel = listPrev->next;
      if (listToDel == ht[i].end)
        ht[i].end = listPrev;
      listPrev->next = listToDel->next;
      free(listToDel->str);
      free(listToDel);
      if (ht[i].list == ht[i].end) {
        free(ht[i].list);
        ht[i].list = ht[i].end = NULL;
      }
      ht[i].num--;
    }
  }
}

void DestroyHTable(htable_t ht[]) {
  int i;
  list_t* cur, *next;

  for (i = 0; i < N; i++) {
    free(ht[i].str);
    if (ht[i].num > 1) {
      cur = ht[i].list;
      while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
      }
    }
  }
  free(ht);
}

static char* _readLine() {
  int extra = 1;
  char* p = (char*)malloc(STR_MUL + 1), * q = p, * cur = p;

  if (p != NULL) {
    if (fgets(p, STR_MUL + 1, stdin) == NULL) {
      p[0] = 0;
      return p;
    }

    // the memory for a line is allocated in intervals of STR_MUL
    while (p[strlen(p) - 1] != '\n') {
      q = (char*)realloc(p, STR_MUL * (++extra) + 1);
      if (q != NULL) {
        p = q;
        cur = p + STR_MUL * (extra - 1);
        fgets(cur, STR_MUL + 1, stdin);
      }
      else
        break;
    }
    if (p[strlen(p) - 1] == '\n')
      p[strlen(p) - 1] = 0;
  }

  return p;
}

void Run(void) {
  htable_t *ht = (htable_t*)calloc(N, sizeof(htable_t));
  char act;
  char* str;
  list_t* list;
  int i;

  act = getchar();
  while (act != EOF) {
    getchar();
    str = _readLine();

    switch (act) {
    case 'a':
      AddElem(ht, str);
      break;
    case 'r':
      DelElem(ht, str);
      break;
    case 'f':
      if (FindElem(ht, str, &i, &list))
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      break;
    }
    act = getchar();
  }
  DestroyHTable(ht);
}