#ifndef _XORLIST_H__
#define _XORLIST_H__

#define MAX_STR 20

#define FALSE 0
#define TRUE 1

typedef struct list list_t;
struct list {
  int xorAddress;
  char str[MAX_STR];
};

typedef struct xorList xorList_t;
struct xorList {
  list_t* first;
  list_t* second;
};

int AddElementToList( xorList_t *list, char* newElement );
int FindElementInListByKey(xorList_t* list, char* key);
int DeleteElementFromListByAddress(xorList_t* list, int address);
int DeleteElementFromListByKey(xorList_t* list, char* key);

typedef struct xorIter xorIter_t;
struct xorIter {
  list_t* container;
  list_t* next;
};
int createIterator(xorIter_t *iter, xorList_t* list);
char* getFromIter(xorIter_t iter);
int nextInIter(xorIter_t* iter);

int clearList(xorList_t*list);

#endif _XORLIST_H__