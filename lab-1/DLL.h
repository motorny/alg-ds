#ifndef DLL_H_
#define DLL_H_


#define MAX_SIZE 15
#define LIST_SIZE 6

typedef struct data_t {
  char value[MAX_SIZE];
} data_t;

typedef struct node_t {
  data_t value;
  struct node_t* next;
  struct node_t* prev;
} node_t;

typedef struct list_t {
  node_t* head, * tail;
} list_t;

list_t* createList();
void deleteList(list_t** list);
void pushFront(list_t* list, char* value);
data_t popFront(list_t* list);
void pushBack(list_t* list, char* value);
void insertBeforeElement(list_t* list, node_t* elm, char* value);
int insertionSort(list_t** List);

#endif // !DLL_H_
