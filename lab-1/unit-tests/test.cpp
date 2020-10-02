#include "pch.h"
extern "C" {
#include "..\skipList.h"
}

skipList* GetSkiplistMockLevel_1(void) {
  skipList* list;
  skipList_Item* item0;
  int keys[] = { 1 };
  int levels[] = { 1 };

  //item :     0
  //lvl_1: --------> NULL
  //lvl_0: -> [ ] -> NULL
  //key  :    <1>
  //value:    {-}

  list = skipList_Get(2);
  item0 = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (item0 == NULL) {
    return NULL;
  }
  item0->value = NULL;
  item0->key = keys[0];
  item0->levelCount = levels[0];

  item0->nextItem_array = (skipList_Item**)calloc(item0->levelCount, sizeof(skipList_Item*));
  if (item0->nextItem_array == NULL) {
    return NULL;
  }
  list->statrItem.nextItem_array[0] = item0;

  return list;
}

skipList* GetSkiplistMockLevel_2(void) {
  skipList* list;
  skipList_Item* item0;
  int keys[] = { 2 };
  int levels[] = { 2 };

  //item :     0
  //lvl_1: -> [ ] -> NULL
  //lvl_0: -> [ ] -> NULL
  //key  :    <2>
  //value:    {-}

  list = skipList_Get(2);
  item0 = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (item0 == NULL) {
    return NULL;
  }
  item0->value = NULL;
  item0->key = keys[0];
  item0->levelCount = levels[0];

  item0->nextItem_array = (skipList_Item**)calloc(item0->levelCount, sizeof(skipList_Item*));
  if (item0->nextItem_array == NULL) {
    return NULL;
  }
  list->statrItem.nextItem_array[0] = item0;
  list->statrItem.nextItem_array[1] = item0;

  return list;
}

skipList* GetSkiplistMockKeys_11(void) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 1, 1 };
  int levels[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <1>
  //value:    {-}    {-}

  list = skipList_Get(2);
  item0 = (skipList_Item*)malloc(sizeof(skipList_Item));
  item1 = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (item0 == NULL || item1 == NULL) {
    return NULL;
  }
  item0->value = NULL;
  item1->value = NULL;

  item0->key = keys[0];
  item0->levelCount = levels[0];

  item1->key = keys[1];
  item1->levelCount = levels[1];

  item0->nextItem_array = (skipList_Item**)calloc(item0->levelCount, sizeof(skipList_Item*));
  item1->nextItem_array = (skipList_Item**)calloc(item1->levelCount, sizeof(skipList_Item*));
  if (item0->nextItem_array == NULL || item1->nextItem_array == NULL) {
    return NULL;
  }
  list->statrItem.nextItem_array[0] = item1;
  list->statrItem.nextItem_array[1] = item1;
  item1->nextItem_array[0] = item0;
  
  return list;
}

skipList* GetSkiplistMockKeys_02(void) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 0, 2 };
  int levels[] = { 1, 2 };

  //item :     0      1
  //lvl_1: --------> [ ] -> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <0>    <2>
  //value:    {-}    {-}

  list = skipList_Get(2);
  item0 = (skipList_Item*)malloc(sizeof(skipList_Item));
  item1 = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (item0 == NULL || item1 == NULL) {
    return NULL;
  }
  item0->value = NULL;
  item1->value = NULL;

  item0->key = keys[0];
  item0->levelCount = levels[0];

  item1->key = keys[1];
  item1->levelCount = levels[1];

  item0->nextItem_array = (skipList_Item**)calloc(item0->levelCount, sizeof(skipList_Item*));
  item1->nextItem_array = (skipList_Item**)calloc(item1->levelCount, sizeof(skipList_Item*));
  if (item0->nextItem_array == NULL || item1->nextItem_array == NULL) {
    return NULL;
  }
  list->statrItem.nextItem_array[0] = item0;
  list->statrItem.nextItem_array[1] = item1;
  item0->nextItem_array[0] = item1;
  
  return list;
}

skipList* GetSkiplistMockKeys_20(void) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 2, 0 };
  int levels[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <0>    <2>
  //value:    {-}    {-}

  list = skipList_Get(2);
  item0 = (skipList_Item*)malloc(sizeof(skipList_Item));
  item1 = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (item0 == NULL || item1 == NULL) {
    return NULL;
  }
  item0->value = NULL;
  item1->value = NULL;

  item0->key = keys[0];
  item0->levelCount = levels[0];

  item1->key = keys[1];
  item1->levelCount = levels[1];

  item0->nextItem_array = (skipList_Item**)calloc(item0->levelCount, sizeof(skipList_Item*));
  item1->nextItem_array = (skipList_Item**)calloc(item1->levelCount, sizeof(skipList_Item*));
  if (item0->nextItem_array == NULL || item1->nextItem_array == NULL) {
    return NULL;
  }
  list->statrItem.nextItem_array[0] = item1;
  list->statrItem.nextItem_array[1] = item1;
  item1->nextItem_array[0] = item0;

  return list;
}

void FreeSkiplistMock(skipList* list) {
  skipList_Free(list);
}

TEST(skipList_Add, NullList_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  int keys[]   = { 1 };
  int levels[] = { 1 };
  int values[] = { 1 };

  list = NULL;
  item = skipList_Add(list, &(values[0]), keys[0], levels[0]);

  EXPECT_TRUE(item == NULL);
}

TEST(skipList_Add, InvalidLevel_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  int keys[]   = { 1 };
  int levels[] = {-1 };
  int values[] = { 1 };

  list = skipList_Get(2);
  item = skipList_Add(list, &(values[0]), keys[0], levels[0]);

  EXPECT_TRUE(item == NULL);

  skipList_Free(list);
}

TEST(skipList_Add, OneItem_ReturnValidVal) {
  skipList* list;
  skipList_Item* item0;

  int keys[] = { 1 };
  int levels[] = { 1 };
  int values[] = { 1 };

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);

  EXPECT_TRUE(item0 != NULL);
  EXPECT_TRUE(item0->key == keys[0]);
  EXPECT_TRUE(item0->levelCount == levels[0]);
  EXPECT_TRUE(item0->value == values + 0);

  skipList_Free(list);
}

TEST(skipList_Add, OneItemLevel1_CorrectPointers) {
  skipList* list;
  skipList_Item* item0;

  int keys[] = { 1 };
  int levels[] = { 1 };
  int values[] = { 1 };

  //item :     0      
  //lvl_1: --------> NULL
  //lvl_0: -> [ ] -> NULL
  //key  :    <1>
  //value:    {1}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);

  EXPECT_TRUE(list->statrItem.nextItem_array[0] == item0);
  EXPECT_TRUE(list->statrItem.nextItem_array[1] == NULL);
  EXPECT_TRUE(item0->nextItem_array[0] == NULL);

  skipList_Free(list);
}

TEST(skipList_Add, OneItemLevel2_CorrectPointers) {
  skipList* list;
  skipList_Item* item0;

  int keys[] = { 1 };
  int levels[] = { 2 };
  int values[] = { 1 };

  //item :     0      
  //lvl_1: -> [ ] -> NULL
  //lvl_0: -> [ ] -> NULL
  //key  :    <1>
  //value:    {1}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);

  EXPECT_TRUE(list->statrItem.nextItem_array[0] == item0);
  EXPECT_TRUE(list->statrItem.nextItem_array[1] == item0);
  EXPECT_TRUE(item0->nextItem_array[0] == NULL);
  EXPECT_TRUE(item0->nextItem_array[1] == NULL);

  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys11_ReturnValidVal) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 1, 1 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <1>
  //value:    {2}    {1}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(item0->key == keys[0] && item0->levelCount == levels[0] && item0->value == values + 0);
  EXPECT_TRUE(item1->key == keys[1] && item1->levelCount == levels[1] && item1->value == values + 1);

  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys12_ReturnValidVal) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 1, 2 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     0      1
  //lvl_1: --------> [ ] -> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <2>
  //value:    {1}    {2}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(item0->key == keys[0] && item0->levelCount == levels[0] && item0->value == values + 0);
  EXPECT_TRUE(item1->key == keys[1] && item1->levelCount == levels[1] && item1->value == values + 1);

  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys21_ReturnValidVal) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 2, 1 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <2>
  //value:    {2}    {1}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(item0->key == keys[0] && item0->levelCount == levels[0] && item0->value == values + 0);
  EXPECT_TRUE(item1->key == keys[1] && item1->levelCount == levels[1] && item1->value == values + 1);

  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys11_Sorted) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[] = { 1, 1 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <1>
  //value:    {2}    {1}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(item1 == list->statrItem.nextItem_array[0]);
  EXPECT_TRUE(item0 == list->statrItem.nextItem_array[0]->nextItem_array[0]);

  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys12_Sorted) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[]   = { 1, 2 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     0      1
  //lvl_1: --------> [ ] -> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <2>
  //value:    {1}    {2}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(item0 == list->statrItem.nextItem_array[0]);
  EXPECT_TRUE(item1 == list->statrItem.nextItem_array[0]->nextItem_array[0]);

  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys21_Sorted) {
  skipList* list;
  skipList_Item* item0, * item1;
  int keys[]   = { 2, 1 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <2>
  //value:    {2}    {1}

  list = skipList_Get(2);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(item1 == list->statrItem.nextItem_array[0]);
  EXPECT_TRUE(item0 == list->statrItem.nextItem_array[0]->nextItem_array[0]);
  
  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys11_CorrectPointers) {
  skipList* list;
  skipList_Item* startItem, * item0, * item1;
  int keys[] = { 1, 1 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <1>
  //value:    {2}    {1}

  list = skipList_Get(2);
  startItem = &(list->statrItem);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(startItem->nextItem_array[0] == item1);
  EXPECT_TRUE(startItem->nextItem_array[1] == item1);
  EXPECT_TRUE(item1->nextItem_array[0] == item0);
  EXPECT_TRUE(item1->nextItem_array[1] == NULL);
  EXPECT_TRUE(item0->nextItem_array[0] == NULL);
  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys12_CorrectPointers) {
  skipList* list;
  skipList_Item* startItem, * item0, * item1;
  int keys[]   = { 1, 2 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     0      1
  //lvl_1: --------> [ ] -> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <2>
  //value:    {1}    {2}

  list = skipList_Get(2);
  startItem = &(list->statrItem);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(startItem->nextItem_array[0] == item0);
  EXPECT_TRUE(startItem->nextItem_array[1] == item1);
  EXPECT_TRUE(item0->nextItem_array[0] == item1);
  EXPECT_TRUE(item1->nextItem_array[0] == NULL);
  EXPECT_TRUE(item1->nextItem_array[1] == NULL);
  skipList_Free(list);
}

TEST(skipList_Add, TwoItemsKeys21_CorrectPointers) {
  skipList* list;
  skipList_Item* startItem, * item0, * item1;
  int keys[]   = { 2, 1 };
  int levels[] = { 1, 2 };
  int values[] = { 1, 2 };

  //item :     1      0
  //lvl_1: -> [ ] --------> NULL
  //lvl_0: -> [ ] -> [ ] -> NULL
  //key  :    <1>    <2>
  //value:    {2}    {1}

  list = skipList_Get(2);
  startItem = &(list->statrItem);
  item0 = skipList_Add(list, &(values[0]), keys[0], levels[0]);
  item1 = skipList_Add(list, &(values[1]), keys[1], levels[1]);

  EXPECT_TRUE(startItem->nextItem_array[0] == item1);
  EXPECT_TRUE(startItem->nextItem_array[1] == item1);
  EXPECT_TRUE(item1->nextItem_array[0] == item0);
  EXPECT_TRUE(item1->nextItem_array[1] == NULL);
  EXPECT_TRUE(item0->nextItem_array[0] == NULL);
  skipList_Free(list);
}

TEST(skipList_Find, NullList_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = NULL;
  item = skipList_Find(list, 1);

  EXPECT_TRUE(item == NULL);
}

TEST(skipList_Find, ZeroItem_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = skipList_Get(2);
  item = skipList_Find(list, 0);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, OneItemLevel1TooBigKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockLevel_1();
  item = skipList_Find(list, 2);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, OneItemLevel1TooSmallKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockLevel_1();
  item = skipList_Find(list, 0);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, OneItemLevel1ValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockLevel_1();
  item = skipList_Find(list, 1);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, OneItemLevel2TooBigKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockLevel_2();
  item = skipList_Find(list, 3);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, OneItemLevel2TooSmallKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockLevel_2();
  item = skipList_Find(list, 0);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, OneItemLevel2ValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockLevel_2();
  item = skipList_Find(list, 2);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys11TooBigKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_11();
  item = skipList_Find(list, 2);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys11TooSmallKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_11();
  item = skipList_Find(list, 0);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys11ValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_11();
  item = skipList_Find(list, 1);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys02MidKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_02();
  item = skipList_Find(list, 1);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys02FirstValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_02();
  item = skipList_Find(list, 0);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys02SecondValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_02();
  item = skipList_Find(list, 2);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]->nextItem_array[0]);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys20MidKey_ReturnNull) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_20();
  item = skipList_Find(list, 1);

  EXPECT_TRUE(item == NULL);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys20FirstValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_20();
  item = skipList_Find(list, 0);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]);
  FreeSkiplistMock(list);
}

TEST(skipList_Find, TwoItemsKeys20SecondValidKey_ReturnValidVal) {
  skipList* list;
  skipList_Item* item;

  list = GetSkiplistMockKeys_20();
  item = skipList_Find(list, 2);

  EXPECT_TRUE(item == list->statrItem.nextItem_array[0]->nextItem_array[0]);
  FreeSkiplistMock(list);
}