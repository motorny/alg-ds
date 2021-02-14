#include "pch.h"
#include <string.h>
#include <math.h>

extern "C" {
  #include "XORlist.h"
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST (AddElementToList_EmptyList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");
  ASSERT_EQ(strcmp(list.first->str, "newElement"), 0);
  ASSERT_EQ(list.first->xorAddress, 0);
  ASSERT_EQ(list.second, nullptr);

  clearList(&list);
}

TEST (AddElementToList_1ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");

  AddElementToList(&list, "newElement2");
  ASSERT_EQ(strcmp(list.second->str, "newElement2"), 0);
  ASSERT_EQ(list.second->xorAddress, 0);

  clearList(&list);
}

TEST (AddElementToList_2ElementsInList_returnTrue) {
  xorList_t list = { NULL, NULL };
  list_t* tmp;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");

  AddElementToList(&list, "newElement3");
  tmp = (list_t*)((int)list.first ^ list.second->xorAddress);
  ASSERT_EQ(strcmp(tmp->str, "newElement3"), 0);
  ASSERT_EQ(tmp->xorAddress, ((int)list.second ^ (int)list.first));

  clearList(&list);
}

TEST (AddElementToList_3andMoreElementsInList_returnTrue) {
  xorList_t list = { NULL, NULL };
  list_t* tmp;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");

  AddElementToList(&list, "newElement4");
  tmp = (list_t*)((int)list.second ^ ((list_t*)((int)list.first ^ list.second->xorAddress))->xorAddress);
  ASSERT_EQ(strcmp(tmp->str, "newElement4"), 0);
  ASSERT_EQ(tmp->xorAddress, (int)((int)list.first ^ ((int)list.first ^ list.second->xorAddress)));

  clearList(&list);
}

TEST (AddElementToList_UppercaseString_returnFalse) {
  xorList_t list = { NULL, NULL };

  ASSERT_EQ(AddElementToList(&list, "012345678901234567890123456789"), 0);
  ASSERT_EQ(list.first, nullptr);
}

TEST (FindElementInListByKey_UppercaseString_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");

  ASSERT_EQ(FindElementInListByKey(&list, "012345678901234567890123456789"), 0);

  clearList(&list);
}

TEST (FindElementInListByKey_EmptyList_returnFalse) {
  xorList_t list = { NULL, NULL };

  ASSERT_EQ(FindElementInListByKey(&list, "element"), 0);
  ASSERT_EQ(list.first, nullptr);
  ASSERT_EQ(list.second, nullptr);
}

TEST (FindElementInListByKey_1ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");
  ASSERT_EQ(FindElementInListByKey(&list, "newElement"), 1);

  clearList(&list);
}

TEST (FindElementInListByKey_1ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");
  ASSERT_EQ(FindElementInListByKey(&list, "oldElement"), 0);

  clearList(&list);
}

TEST (FindElementInListByKey_2andMoreElementsList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  ASSERT_EQ(FindElementInListByKey(&list, "newElement1"), 1);
  ASSERT_EQ(FindElementInListByKey(&list, "newElement2"), 1);

  clearList(&list);
}

TEST (FindElementInListByKey_2andMoreElementsList_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElemen1");
  AddElementToList(&list, "newElemen2");
  ASSERT_EQ(FindElementInListByKey(&list, "newElement3"), 0);
  ASSERT_EQ(FindElementInListByKey(&list, "oldElement"), 0);

  clearList(&list);
}


TEST (DeleteElementFromListByKey_UppercaseString_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");

  ASSERT_EQ(DeleteElementFromListByKey(&list, "012345678901234567890123456789"), 0);
  ASSERT_EQ(strcmp(list.first->str, "newElement"), 0);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_EmptyList_returnFalse) {
  xorList_t list = { NULL, NULL };

  ASSERT_EQ(DeleteElementFromListByKey(&list, "element"), 0);
  ASSERT_EQ(list.first, nullptr);
  ASSERT_EQ(list.second, nullptr);
}

TEST (DeleteElementFromListByKey_1ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "element"), 0);
  ASSERT_EQ(strcmp(list.first->str, "newElement"), 0);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_1ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement"), 1);
  ASSERT_EQ(list.first, nullptr);
}

TEST (DeleteElementFromListByKey_2ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement3"), 0);
  ASSERT_EQ(DeleteElementFromListByKey(&list, "oldElement"), 0);
  ASSERT_EQ(strcmp(list.first->str, "newElement1"), 0);
  ASSERT_EQ(strcmp(list.second->str, "newElement2"), 0);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_2ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement2"), 1);
  ASSERT_EQ(strcmp(list.first->str, "newElement1"), 0);
  ASSERT_EQ(list.second, nullptr);

  AddElementToList(&list, "newElement2");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement1"), 1);
  ASSERT_EQ(strcmp(list.first->str, "newElement2"), 0);
  ASSERT_EQ(list.second, nullptr);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_3ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");

  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement3"), 1);
  ASSERT_EQ(fabs(strcmp(list.second->str, "newElement3") / strcmp(list.second->str, "newElement3")), 1);
  ASSERT_EQ(fabs(strcmp(list.first->str, "newElement3") / strcmp(list.first->str, "newElement3")), 1);

  AddElementToList(&list, "newElement3");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement1"), 1);
  ASSERT_EQ(fabs(strcmp(list.second->str, "newElement1") / strcmp(list.second->str, "newElement1")), 1);
  ASSERT_EQ(fabs(strcmp(list.first->str, "newElement1") / strcmp(list.first->str, "newElement1")), 1);

  AddElementToList(&list, "newElement1");
  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement2"), 1);
  ASSERT_EQ(fabs(strcmp(list.second->str, "newElement2") / strcmp(list.second->str, "newElement2")), 1);
  ASSERT_EQ(fabs(strcmp(list.first->str, "newElement2") / strcmp(list.first->str, "newElement2")), 1);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_3ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };
  list_t* tmp;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");

  tmp = (list_t*)((int)list.first ^ list.second->xorAddress);

  ASSERT_EQ(DeleteElementFromListByKey(&list, "oldElement"), 0);
  ASSERT_EQ(strcmp(list.first->str, "newElement1"), 0);
  ASSERT_EQ(strcmp(list.second->str, "newElement2"), 0);
  ASSERT_EQ(strcmp(tmp->str, "newElement3"), 0);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_MoreThan3ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };
  list_t* tmp1, * tmp2;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");
  AddElementToList(&list, "newElement4");

  tmp1 = (list_t*)((int)list.first ^ list.second->xorAddress);
  tmp2 = (list_t*)((int)list.second ^ tmp1->xorAddress);

  ASSERT_EQ(DeleteElementFromListByKey(&list, "oldElement"), 0);
  ASSERT_EQ(strcmp(list.first->str, "newElement1"), 0);
  ASSERT_EQ(strcmp(list.second->str, "newElement2"), 0);
  ASSERT_EQ(strcmp(tmp1->str, "newElement3"), 0);
  ASSERT_EQ(strcmp(tmp2->str, "newElement4"), 0);

  clearList(&list);
}

TEST (DeleteElementFromListByKey_MoreThan3ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };
  list_t* tmp1, * tmp2;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");
  AddElementToList(&list, "newElement4");

  tmp1 = (list_t*)((int)list.first ^ list.second->xorAddress);
  tmp2 = (list_t*)((int)list.second ^ tmp1->xorAddress);

  ASSERT_EQ(DeleteElementFromListByKey(&list, "newElement4"), 1);
  ASSERT_EQ(fabs(strcmp(list.first->str, "newElement4") / strcmp(list.first->str, "newElement4")), 1);
  ASSERT_EQ(fabs(strcmp(list.second->str, "newElement4") / strcmp(list.second->str, "newElement4")), 1);
  ASSERT_EQ(fabs(strcmp(tmp1->str, "newElement4") / strcmp(tmp1->str, "newElement4")), 1);

  clearList(&list);
}

TEST (DeleteElementFromListByAddress_EmptyList_returnFalse) {
  xorList_t list = { NULL, NULL };

  ASSERT_EQ(DeleteElementFromListByAddress(&list, 1), 0);
  ASSERT_EQ(list.first, nullptr);
  ASSERT_EQ(list.second, nullptr);
}

TEST (DeleteElementFromListByAddress_1ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");
  ASSERT_EQ(DeleteElementFromListByAddress(&list, 1), 0);
  ASSERT_EQ(list.first->xorAddress, 0);
  ASSERT_EQ(list.second, nullptr);

  clearList(&list);
}

TEST (DeleteElementFromListByAddress_2ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");

  ASSERT_EQ(DeleteElementFromListByAddress(&list, 1), 0);
  ASSERT_EQ(list.first->xorAddress, 0);
  ASSERT_EQ(list.second->xorAddress, 0);

  clearList(&list);
}

TEST (DeleteElementFromListByAddress_3ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };
  list_t* tmp;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");

  tmp = (list_t*)((int)list.first ^ list.second->xorAddress);

  ASSERT_EQ(DeleteElementFromListByAddress(&list, tmp->xorAddress), 1);
  ASSERT_EQ(list.first->xorAddress, 0);
  ASSERT_EQ(list.second->xorAddress, 0);

  clearList(&list);
}

TEST (DeleteElementFromListByAddress_3ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };
  list_t* tmp;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");

  tmp = (list_t*)((int)list.first ^ list.second->xorAddress);

  ASSERT_EQ(DeleteElementFromListByAddress(&list, 0), 0);
  ASSERT_EQ(list.first->xorAddress / list.first->xorAddress, 1);
  ASSERT_EQ(list.second->xorAddress / list.second->xorAddress, 1);

  clearList(&list);
}

TEST (DeleteElementFromListByAddress_More3ElementList_returnFalse) {
  xorList_t list = { NULL, NULL };
  list_t* tmp1, * tmp2;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");
  AddElementToList(&list, "newElement4");

  tmp1 = (list_t*)((int)list.first ^ list.second->xorAddress);
  tmp2 = (list_t*)((int)list.second ^ tmp1->xorAddress);

  ASSERT_EQ(DeleteElementFromListByAddress(&list, 0), 0);
  ASSERT_EQ(list.first->xorAddress / list.first->xorAddress, 1);
  ASSERT_EQ(list.second->xorAddress / list.second->xorAddress, 1);
  ASSERT_EQ(tmp2->xorAddress, ((int)tmp1 ^ (int)list.first));

  clearList(&list);
}

TEST (DeleteElementFromListByAddress_More3ElementList_returnTrue) {
  xorList_t list = { NULL, NULL };
  list_t* tmp1, * tmp2;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");
  AddElementToList(&list, "newElement4");

  tmp1 = (list_t*)((int)list.first ^ list.second->xorAddress);
  tmp2 = (list_t*)((int)list.second ^ tmp1->xorAddress);

  ASSERT_EQ(DeleteElementFromListByAddress(&list, tmp2->xorAddress), 1);

  clearList(&list);
}

TEST(createIterator_EmptyList_returnTrue) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  ASSERT_EQ(createIterator(&iter, &list), 1);
  ASSERT_EQ(iter.container, nullptr);
  ASSERT_EQ(iter.next, nullptr);
}

TEST(createIterator_1ElemList_returnTrue) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  ASSERT_EQ(createIterator(&iter, &list), 1);
  ASSERT_EQ(iter.container, list.first);
  ASSERT_EQ(iter.next, nullptr);
  
  clearList(&list);
}

TEST(createIterator_2andMoreElemList_returnTrue) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  ASSERT_EQ(createIterator(&iter, &list), 1);
  ASSERT_EQ(iter.container, list.first);
  ASSERT_EQ(iter.next, list.second);

  clearList(&list);
}

TEST(getFromIter_EmptyList_returnFalse) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  createIterator(&iter, &list);
  ASSERT_EQ(getFromIter(iter), nullptr); // <-- "" == 0, ò.å. FALSE
}

TEST(getFromIter_1ElemList_returnValue) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  createIterator(&iter, &list);
  ASSERT_EQ(strcmp(getFromIter(iter), "newElement1"), 0);
  clearList(&list);
}

TEST(getFromIter_2andMoreElemList_returnValue) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  createIterator(&iter, &list);
  ASSERT_EQ(strcmp(getFromIter(iter), "newElement1"), 0);
  clearList(&list);
}

TEST(nextInIter_EmptyList_returnFalse) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;
 
  createIterator(&iter, &list);
  ASSERT_EQ(nextInIter(&iter), 0);
}

TEST(nextInIter_1ElemList_returnFalse) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  createIterator(&iter, &list);
  ASSERT_EQ(nextInIter(&iter), 0);
  clearList(&list);
}

TEST(nextInIter_2ElemList_returnTrue) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  createIterator(&iter, &list);
  ASSERT_EQ(nextInIter(&iter), 1);
  ASSERT_EQ(strcmp(getFromIter(iter), "newElement2"), 0);
  clearList(&list);
}

TEST(nextInIter_3andMoreElemList_returnFalse) {
  xorList_t list = { NULL, NULL };
  xorIter_t iter;

  AddElementToList(&list, "newElement1");
  AddElementToList(&list, "newElement2");
  AddElementToList(&list, "newElement3");
  createIterator(&iter, &list);
  ASSERT_EQ(nextInIter(&iter), 1);
  ASSERT_EQ(strcmp(getFromIter(iter), "newElement2"), 0);
  ASSERT_EQ(nextInIter(&iter), 1);
  ASSERT_EQ(strcmp(getFromIter(iter), "newElement3"), 0);
  clearList(&list);
} 
