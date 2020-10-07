#include "pch.h"

extern "C" {
#include "..\LabA\Header.h"
#include "..\LabA\LabA.c"
}
/*
TEST(TestCaseName, TestName) {
  ASSERT_EQ(1, 1);
}
*/

table_t* InitTable(int id1, int id2) {
  table_t* table = (table_t*)malloc(sizeof(table_t));
  elem_t* elem1 = NULL, * elem2 = NULL;
  line_t* line1 = NULL, * line2 = NULL;

  elem_t* ptr = NULL; //putting ID using this

  elem1 = (elem_t*)malloc(sizeof(elem_t));
  line1 = (line_t*)malloc(sizeof(line_t));

  elem1->line = line1;
  table->head = elem1;

  elem2 = (elem_t*)malloc(sizeof(elem_t));
  line2 = (line_t*)malloc(sizeof(elem_t));

  elem1->next = elem2;
  elem2->line = line2;
  elem2->next = NULL;

  ptr = table->head;

  ptr->line->id = id1;
  ptr = ptr->next;
  ptr->line->id = id2;
  return table;
}

int IsSortedList(table_t* table) {
  elem_t* ptr1 = table->head;
  elem_t* ptr2 = table->head->next;

  while (ptr2 != NULL) {
    if (ptr1->line->id > ptr2->line->id)
      return 0;

    ptr1 = ptr2;
    ptr2 = ptr2->next;
  }
  return 1;
}

int NumberOfElements(table_t* table) {
  elem_t* ptr = table->head;
  int k = 0;

  while (ptr != NULL) {
    ptr = ptr->next;
    k++;
  }
  return k;
}

TEST(Building, BuildTable_TableIsNull_ReturnsNull) {
  table_t* table = BuildTable(NULL);
  ASSERT_EQ(table, (table_t*)NULL);
}

TEST(Building, BuildTable_ValidTable_ReturnsValidPtr) {
  FILE* filename = fopen("input2.txt", "r"); //exists
  ASSERT_NE(filename, (FILE*)NULL);
  table_t* table = BuildTable(filename);
  ASSERT_NE(table, (table_t*)NULL);
  ASSERT_STREQ(table->head->line->name, "Sobolev");
  ASSERT_STREQ(table->head->next->line->name, "Nikitin");
  ASSERT_STREQ(table->head->next->next->line->name, "Pushkin");
}

TEST(Merge, MergeTable_AnyTableIsNULL_ReturnsNULL) {
  table_t* table1 = InitTable(0, 0);
  table_t* table2 = NULL;
  table_t* table3 = NULL;

  table3 = MergeTable(table1, table2);
  ASSERT_EQ(table3, (table_t*)NULL);


  table3 = MergeTable(table2, table1);
  ASSERT_EQ(table3, (table_t*)NULL);

  DestroyTable(table1);
}

TEST(Merge, MergeTable_AllElementsOfOneListGreaterThanElementsOfOther_ReturnsSortedTable) {
  table_t* smallTable = InitTable(1, 2);
  int elementsSmall = NumberOfElements(smallTable);
  table_t* bigTable = InitTable(3, 4);
  int elementsBig = NumberOfElements(bigTable);
  table_t* Table = MergeTable(smallTable, bigTable);
  ASSERT_EQ(IsSortedList(Table), 1);
  ASSERT_EQ(elementsSmall + elementsBig, NumberOfElements(Table)); //number of elements
  DestroyTable(Table);
}


TEST(Merge, MergeTable_AllElementsAreEqual_ReturnsSortedTable) {
  table_t* table1 = InitTable(1, 1);
  int elements1 = NumberOfElements(table1);
  table_t* table2 = InitTable(1, 1);
  int elements2 = NumberOfElements(table2);
  table_t* table = MergeTable(table1, table2);
  ASSERT_EQ(IsSortedList(table), 1);
  ASSERT_EQ(elements1 + elements2, NumberOfElements(table));
  DestroyTable(table);
}

TEST(Merge, MergeTable_UsualCase_ReturnsSortedTable) {
  table_t* table1 = InitTable(1, 3);
  int elements1 = NumberOfElements(table1);
  table_t* table2 = InitTable(2, 4);
  int elements2 = NumberOfElements(table2);
  table_t* table = MergeTable(table1, table2);
  ASSERT_EQ(IsSortedList(table), 1);
  ASSERT_EQ(elements1 + elements2, NumberOfElements(table));
  DestroyTable(table);
}