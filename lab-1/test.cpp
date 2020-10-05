#include "pch.h"
extern "C"
{
  #include "DLL.h"
}

list_t* CreateTestList(char buf0[], char buf1[], char buf2[], char buf3[], char buf4[], char buf5[])
{
  list_t *list = (list_t *)malloc(sizeof(list_t));
  node_t* el1 = (node_t*)malloc(sizeof(node_t));
  node_t* el2 = (node_t*)malloc(sizeof(node_t));
  node_t* el3 = (node_t*)malloc(sizeof(node_t));
  node_t* el4 = (node_t*)malloc(sizeof(node_t));
  node_t* el5 = (node_t*)malloc(sizeof(node_t));
  node_t* el6 = (node_t*)malloc(sizeof(node_t));
  
  list->head = el1;
  list->tail = el6;

  el1->next = el2;
  el2->next = el3;
  el3->next = el4;
  el4->next = el5;
  el5->next = el6;
  el6->next = NULL;

  el1->prev = NULL;
  el2->prev = el1;
  el3->prev = el2;
  el4->prev = el3;
  el5->prev = el4;
  el6->prev = el5;

  strcpy(el1->value.value, buf0);
  strcpy(el2->value.value, buf1);
  strcpy(el3->value.value, buf2);
  strcpy(el4->value.value, buf3);
  strcpy(el5->value.value, buf4);
  strcpy(el6->value.value, buf5);

  return list;
}

TEST(pushFront_EmptyList_returnTrue) {
  list_t *l = createList();

  pushFront(l, "Element0");
  ASSERT_EQ(l->head, l->tail);
  ASSERT_EQ(strcmp(l->head->value.value, "Element0"), 0);
  deleteList(&l);
}

TEST(pushFront_1ElementList_returnTrue) {
  list_t *l = createList();
  node_t* el = (node_t*)malloc(sizeof(node_t));
  char buf[300] = "Element0";
  l->head = l->tail = el;
  strcpy(el->value.value, buf);
  el->prev = el->next = NULL;

  pushFront(l, "Element1");
  ASSERT_EQ(l->head->next, l->tail);
  ASSERT_EQ(strcmp(l->head->value.value, "Element1"), 0);
  ASSERT_EQ(strcmp(l->tail->prev->value.value, "Element1"), 0);
  deleteList(&l);
}

TEST(pushFront_2ElementList_returnTrue) {
  list_t *l = createList();
  node_t* el1 = (node_t*)malloc(sizeof(node_t));
  node_t* el2 = (node_t*)malloc(sizeof(node_t));
  char buf1[300] = "Element0";
  char buf2[300] = "Element1";
  l->head = el1;
  l->tail = el2;
  el1->prev = el2->next = NULL;
  el1->next = el2;
  el2->prev = el1;
  strcpy(el1->value.value, buf1);
  strcpy(el2->value.value, buf2);

  pushFront(l, "Element2");
  ASSERT_EQ(l->head->next, l->tail->prev);
  ASSERT_EQ(strcmp(l->head->value.value, "Element2"), 0);
  ASSERT_EQ(strcmp(l->tail->prev->prev->value.value, "Element2"),0);
  deleteList(&l);
}

TEST(pushBack_EmptyList_returnTrue) {
  list_t* l = createList();

  pushBack(l, "Element0");
  ASSERT_EQ(l->head, l->tail);
  ASSERT_EQ(strcmp(l->tail->value.value, "Element0"), 0);
  deleteList(&l);
}

TEST(pushBack_1ElementList_returnTrue) {
  list_t* l = createList();
  node_t* el = (node_t*)malloc(sizeof(node_t));
  char buf[300] = "Element0";
  l->head = l->tail = el;
  strcpy(el->value.value, buf);
  el->prev = el->next = NULL;

  pushBack(l, "Element1");
  ASSERT_EQ(l->tail->prev, l->head);
  ASSERT_EQ(strcmp(l->tail->value.value, "Element1"), 0);
  ASSERT_EQ(strcmp(l->head->next->value.value, "Element1"), 0);
  deleteList(&l);
}

TEST(pushBack_2ElementList_returnTrue) {
  list_t* l = createList();
  node_t* el1 = (node_t*)malloc(sizeof(node_t));
  node_t* el2 = (node_t*)malloc(sizeof(node_t));
  char buf1[300] = "Element0";
  char buf2[300] = "Element1";
  l->head = el1;
  l->tail = el2;
  el1->prev = el2->next = NULL;
  el1->next = el2;
  el2->prev = el1;
  strcpy(el1->value.value, buf1);
  strcpy(el2->value.value, buf2);

  pushBack(l, "Element2");
  ASSERT_EQ(l->head->next, l->tail->prev);
  ASSERT_EQ(strcmp(l->tail->value.value, "Element2"), 0);
  ASSERT_EQ(strcmp(l->head->next->next->value.value, "Element2"), 0);
  deleteList(&l);
}

TEST(popFront_EmptyList_returnError) {
  list_t *l = createList();
  ASSERT_EQ(strcmp(popFront(l).value, ""), 0);
  deleteList(&l);
}

TEST(popFront_1ElementList_returnElement) {
  list_t *l = createList();
  data_t tmp = {0};
  node_t* el = (node_t*)malloc(sizeof(node_t));
  char buf[300] = "Element";
  l->head = l->tail = el;
  strcpy(el->value.value, buf);
  el->prev = el->next = NULL;

  tmp = popFront(l);
  ASSERT_EQ(strcmp(tmp.value, "Element"), 0);
  ASSERT_EQ(l->head, nullptr);
  deleteList(&l);
}

TEST(popFront_2orMoreElementList_returnElement) {
  list_t* l = createList();
  data_t tmp = { 0 };
  node_t* el1 = (node_t*)malloc(sizeof(node_t));
  node_t* el2 = (node_t*)malloc(sizeof(node_t));
  char buf1[300] = "Element";
  char buf2[300] = "Element1";
  l->head = el1;
  l->tail = el2;
  el1->prev = el2->next = NULL;
  el1->next = el2;
  el2->prev = el1;
  strcpy(el1->value.value, buf1);
  strcpy(el2->value.value, buf2);

  tmp = popFront(l);
  ASSERT_EQ(strcmp(tmp.value, "Element"), 0);
  ASSERT_EQ(strcmp(l->head->value.value, "Element1"), 0);
  ASSERT_EQ(l->head, l->tail);
  deleteList(&l);
}

TEST(insertBeforeElement_1ElementList_returnTrue) {
  list_t *l = createList();

  data_t tmp = { 0 };
  node_t* el = (node_t*)malloc(sizeof(node_t));
  char buf[300] = "Element";
  l->head = l->tail = el;
  strcpy(el->value.value, buf);
  el->prev = el->next = NULL;

  node_t* elem = l->head;
  insertBeforeElement(l, elem, "Element");
  ASSERT_EQ(strcmp(l->head->value.value, "Element"), 0);
  ASSERT_EQ(l->head->next, l->tail);
  deleteList(&l);
}

TEST(insertBeforeElement_2ElementList_returnTrue) {
  list_t* l = createList();
  node_t* el1 = (node_t*)malloc(sizeof(node_t));
  node_t* el2 = (node_t*)malloc(sizeof(node_t));
  char buf1[300] = "Element";
  char buf2[300] = "Element1";
  l->head = el1;
  l->tail = el2;
  el1->prev = el2->next = NULL;
  el1->next = el2;
  el2->prev = el1;
  strcpy(el1->value.value, buf1);
  strcpy(el2->value.value, buf2);

  node_t* elem = l->tail;
  insertBeforeElement(l, elem, "Element");
  ASSERT_EQ(strcmp(l->tail->prev->value.value, "Element"), 0);
  ASSERT_EQ(l->head->next, l->tail->prev);
  deleteList(&l);
}

TEST(insertBeforeElement_3orMoreElementList_returnTrue) {
  list_t* l = CreateTestList("Element1", "Element2", "Element3", "Element4", "Element6", "Element7");
  node_t* elem = l->tail->prev;
  insertBeforeElement(l, elem, "Element5");
  ASSERT_EQ(strcmp(l->tail->value.value, "Element7"), 0);
  ASSERT_EQ(strcmp(l->tail->prev->prev->value.value, "Element5"), 0);
  deleteList(&l);
}

TEST(insertionSort_EmtpyList_returnNullptr) {
  list_t* l = createList();
  ASSERT_EQ(insertionSort(&l), 0);
}

TEST(insertionSort_1ElementList_returnElement) {
  list_t* l = createList();
  node_t* el = (node_t*)malloc(sizeof(node_t));
  char buf[300] = "Element";
  l->head = l->tail = el;
  strcpy(el->value.value, buf);
  el->prev = el->next = NULL;
  insertionSort(&l);
  ASSERT_EQ(strcmp(l->head->value.value, "Element"), 0);
}

TEST(insertionSort_MorethenOneElementList_returnSortedLint) {
  char unsortedListElem[LIST_SIZE][MAX_SIZE] = { "acb","vvv","1234","0","hduuuq","gdghdkh" };
  char sortedListElem[LIST_SIZE][MAX_SIZE] = { "0","1234","acb","gdghdkh","hduuuq","vvv" };
  list_t* l = CreateTestList("acb", "vvv", "1234", "0", "hduuuq", "gdghdkh");
  insertionSort(&l);
  node_t* cmp = l->head;
  for (int i = 0; i < LIST_SIZE; i++) {
    ASSERT_EQ(strcmp(cmp->value.value, sortedListElem[i]), 0);
    cmp = cmp->next;
  }
}