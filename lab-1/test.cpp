#include "pch.h"
extern "C"
{
  #include "DLL.h"
}


TEST(pushFront_EmptyList_true) {
  list_t *l = createList();

  pushFront(l, "Element0");
  ASSERT_EQ(l->head, l->tail);
  ASSERT_EQ(strcmp(l->head->value.value, "Element0"), 0);
  deleteList(&l);
}

TEST(pushFront_1ElementList_true) {
  list_t *l = createList();
  pushFront(l, "Element0");

  pushFront(l, "Element1");
  ASSERT_EQ(l->head->next, l->tail);
  ASSERT_EQ(strcmp(l->head->value.value, "Element1"), 0);
  ASSERT_EQ(strcmp(l->tail->prev->value.value, "Element1"), 0);
  deleteList(&l);
}

TEST(pushFront_2ElementList_true) {
  list_t *l = createList();
  pushFront(l, "Element0");
  pushFront(l, "Element1");
  
  pushFront(l, "Element2");
  ASSERT_EQ(l->head->next, l->tail->prev);
  ASSERT_EQ(strcmp(l->head->value.value, "Element2"), 0);
  ASSERT_EQ(strcmp(l->tail->prev->prev->value.value, "Element2"),0);
  deleteList(&l);
}

TEST(pushBack_EmptyList_true) {
  list_t* l = createList();

  pushBack(l, "Element0");
  ASSERT_EQ(l->head, l->tail);
  ASSERT_EQ(strcmp(l->tail->value.value, "Element0"), 0);
  deleteList(&l);
}

TEST(pushBack_1ElementList_true) {
  list_t* l = createList();
  pushBack(l, "Element0");

  pushBack(l, "Element1");
  ASSERT_EQ(l->tail->prev, l->head);
  ASSERT_EQ(strcmp(l->tail->value.value, "Element1"), 0);
  ASSERT_EQ(strcmp(l->head->next->value.value, "Element1"), 0);
  deleteList(&l);
}

TEST(pushBack_2ElementList_true) {
  list_t* l = createList();
  pushBack(l, "Element0");
  pushBack(l, "Element1");

  pushBack(l, "Element2");
  ASSERT_EQ(l->head->next, l->tail->prev);
  ASSERT_EQ(strcmp(l->tail->value.value, "Element2"), 0);
  ASSERT_EQ(strcmp(l->head->next->next->value.value, "Element2"), 0);
  deleteList(&l);
}

TEST(popFront_EmptyList_returnFalse) {
  list_t *l = createList();
  ASSERT_DEATH(popFront(l), "");
  deleteList(&l);
}

TEST(popFront_1ElementList_true) {
  list_t *l = createList();
  data_t tmp = {0};

  pushBack(l, "Element");
  tmp = popFront(l);
  ASSERT_EQ(strcmp(tmp.value, "Element"), 0);
  ASSERT_EQ(l->head, nullptr);
  deleteList(&l);
}

TEST(popFront_2ElementList_true) {
  list_t* l = createList();
  data_t tmp = { 0 };

  pushBack(l, "Element");
  pushBack(l, "Element1");

  tmp = popFront(l);
  ASSERT_EQ(strcmp(tmp.value, "Element"), 0);
  ASSERT_EQ(strcmp(l->head->value.value, "Element1"), 0);
  ASSERT_EQ(l->head, l->tail);
  deleteList(&l);
} // стоит ли писать больше??

/*TEST(insertBeforeElement_EmptyList_returnError) {
  list_t* l = createList();
  node_t* elem = NULL;
  ASSERT_DEATH(insertBeforeElement(l, elem, "Element"), "");
  deleteList(&l);
}
*/

TEST(insertBeforeElement_1ElementList_true) {
  list_t *l = createList();
  pushBack(l, "Element");
  node_t* elem = l->head;
  insertBeforeElement(l, elem, "Element");
  ASSERT_EQ(strcmp(l->head->value.value, "Element"), 0);
  ASSERT_EQ(l->head->next, l->tail);
  deleteList(&l);
}

TEST(insertBeforeElement_2ElementList_true) {
  list_t* l = createList();
  pushBack(l, "Element");
  pushBack(l, "Element1");
  node_t* elem = l->tail;
  insertBeforeElement(l, elem, "Element");
  ASSERT_EQ(strcmp(l->tail->prev->value.value, "Element"), 0);
  ASSERT_EQ(l->head->next, l->tail->prev);
  deleteList(&l);
}

TEST(insertBeforeElement_3orMoreElementList_true) {
  list_t* l = createList();
  pushBack(l, "Element0");
  pushBack(l, "Element1");
  pushBack(l, "Element2");
  node_t* elem = l->tail->prev;
  insertBeforeElement(l, elem, "Element3");
  ASSERT_EQ(strcmp(l->tail->value.value, "Element2"), 0);
  ASSERT_EQ(strcmp(l->tail->prev->prev->value.value, "Element3"), 0);
  deleteList(&l);
}

TEST(insertionSort_EmtpyList_returnNullptr) {
  list_t* l = createList();
  insertionSort(&l);
  ASSERT_EQ((*l).head, nullptr);
}

TEST(insertionSort_1ElementList_returnElement) {
  list_t* l = createList();
  pushBack(l, "Element");
  insertionSort(&l);
  ASSERT_EQ(strcmp(l->head->value.value, "Element"), 0);
}

TEST(insertionSort_MorethenOneElementList_returnSortedLint) {
  list_t* l = createList();
  char unsortedListElem[LIST_SIZE][MAX_SIZE] = {"acb","vvv","1234","0","hduuuq","gdghdkh"};
  char sortedListElem[LIST_SIZE][MAX_SIZE] = {"0","1234","acb","gdghdkh","hduuuq","vvv"};
  for (int i = 0; i < LIST_SIZE; i++) {
    pushBack(l, unsortedListElem[i]);
  }
  insertionSort(&l);
  node_t* cmp = l->head;
  for (int i = 0; i < LIST_SIZE; i++) {
    ASSERT_EQ(strcmp(cmp->value.value, sortedListElem[i]), 0);
    cmp = cmp->next;
  }
}