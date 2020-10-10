#ifndef _UNROLLEDLINKEDLIST_H__
#define _UNROLLEDLINKEDLIST_H__

#define MAX_NUM_OF_ELEM 5  //number of elements in array, which every node contains

#define FALSE 1
#define TRUE 0

#define INVALID_INPUT_DATA -1
#define ELEM_IS_NOT_IN_THE_LIST -2
#define END_OF_THE_LIST -3
#define LIST_IS_EMPTY -4


typedef struct node_t {
	int numElem;
	int arr[MAX_NUM_OF_ELEM];
	struct node_t* next;
} node_t;

typedef struct ullist_t {
	node_t* head;
} ullist_t;

ullist_t* CreateList();
int AddElemToList(ullist_t* list, int numOfElemToInsertAfter, int newElem);
int FindNumOfElemInListByKey(ullist_t* list, int key);
int* FindElemInListByNum(ullist_t* list, int num);
int DeleteElemFromListByNum(ullist_t* list, int num);
int CountNumOfElements(ullist_t* list);
int DeleteList(ullist_t* list);

typedef struct ullIter_t {
	ullist_t* list;
	node_t* node;
	int numOfCurElemInNode;
	int* ptrOnCurElem;
} ullIter_t;

ullIter_t* CreateIterator(ullist_t* list);
int GetFromIterator(ullIter_t* iterator, int* gettingElem);
int NextInIterator(ullIter_t* iterator);

#endif