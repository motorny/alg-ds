#include "Function.h"
#include <gtest/gtest.h>

TEST(TestAdd, AddFail) {
  word_t* first = NULL;

  first = AddItem(first, "Jane", 4);

  EXPECT_EQ(first->size, 4);
  EXPECT_TRUE(!strcmp(first->word, "Jane"));
  EXPECT_TRUE(first->next == NULL);

  AddItem(first, "Jakob", 5);
  AddItem(first, "Johnatan", 8);

  EXPECT_EQ(first->size, 4);
  EXPECT_TRUE(!strcmp(first->word, "Jane"));

  EXPECT_EQ(first->next->size, 5);
  EXPECT_TRUE(!strcmp(first->next->word, "Jakob"));

  EXPECT_EQ(first->next->next->size, 8);
  EXPECT_TRUE(!strcmp(first->next->next->word, "Johnatan"));

  EXPECT_TRUE(first->next->next->next == NULL);
  MemoryFree(first);
}

TEST(TestSort, EmptySortFail) {
  word_t* first = NULL;

  first = SortWords(first);

  EXPECT_TRUE(first == NULL); //empty list we understand as a list consisting of 0 elements, it means that *first == NULL, so we check if SortWords hasn't changed anything
}

TEST(TestSort, SoloSortFail) {
  word_t* first = NULL;

  first = SortWords(AddItem(first, "Jane", 4));

  EXPECT_EQ(first->size, 4);
  EXPECT_TRUE(!strcmp(first->word, "Jane"));
  EXPECT_TRUE(first->next == NULL);

  MemoryFree(first);
}

TEST(TestSort, ComonSortFail) {
  word_t* first = NULL;

  first = AddItem(first, "Jane", 4);
  AddItem(first, "Jakob", 5);
  AddItem(first, "Johnatan", 8);

  first = SortWords(first);
  EXPECT_TRUE(!strcmp(first->word, "Jakob"));
  EXPECT_TRUE(!strcmp(first->next->word, "Jane"));
  EXPECT_TRUE(!strcmp(first->next->next->word, "Johnatan"));
  MemoryFree(first);
}

//TEST()

///////////////////Тело функции///////////////////
/////////////////////////////////////////////////
int main(int argc, char** argv) {
  word_t* first = NULL;

  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  first = AddItem(first, "Walter", 6);
  AddItem(first, "Jane", 4);
  AddItem(first, "Jessy", 5);
  AddItem(first, "Scarlet", 7);
  AddItem(first, "Jessy", 5);

  printf("\n              We had:\n");
  PrintWords(first);
  first = SortWords(first);
  printf("\n              We got:\n");
  PrintWords(first);

  MemoryFree(first);


  return 0;
}