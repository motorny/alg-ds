#include "pch.h"
#include "../list.h"

int compare(const data_t* a, const data_t* b);

TEST(AddToList, NullList_ReturnsError) {
  data_t data = { {24, 9, 20}, 13.4 };
  ASSERT_EQ(AddToList(NULL, &data, &compare), ERROR);
}

TEST(AddToList, NullData_ReturnsError) {
  list_t* list = CreateList();
  ASSERT_EQ(AddToList(list, NULL, &compare), ERROR);
  DeleteList(list);
}

TEST(AddToList, NullCompare_ReturnsError) {
  list_t* list = CreateList();
  data_t data = { {24, 9, 20}, 13.4 };
  ASSERT_EQ(AddToList(list, &data, NULL), ERROR);
  DeleteList(list);
}

TEST(AddToList, EmptyList_ReturnsSUCCESS) {
  list_t* list = CreateList();
  data_t data = { {24, 9, 20}, 13.4 };
  ASSERT_EQ(AddToList(list, &data, &compare), SUCCESS);
  DeleteList(list);
}

TEST(compare, Equil_ReturnsZero) {
  data_t data1 = { {5, 4, 10}, 13 };
  data_t data2 = { {5, 4, 10}, 13 };

 ASSERT_EQ(compare(&data1, &data2), 0);
}

TEST(compare, GT_ReturnsOne) {
  data_t data1 = { {5, 4, 10}, 20 };
  data_t data2 = { {5, 4, 10}, 13 };

  ASSERT_EQ(compare(&data1, &data2), 1);
}

TEST(compare, LT_ReturnsNegariveOne) {
  data_t data1 = { {5, 4, 10}, 13 };
  data_t data2 = { {8, 4, 10}, 13 };

  ASSERT_EQ(compare(&data1, &data2), -1);
}
