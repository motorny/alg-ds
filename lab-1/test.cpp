#include "Function.h"
#include <gtest/gtest.h>

TEST(TestInitialize, InitializeFail) {
  FILE* f = NULL;
  fopen_s(&f,"g_test.txt", "r");
  word_t* first = Initialize(f);
  fclose(f);
  EXPECT_TRUE(first != NOT_ENOUGHT_MEMORY);
  EXPECT_EQ(first->size, 10);
  EXPECT_TRUE(!strcmp(first->word, "9876543210"));
  EXPECT_TRUE(first->next->next == NULL);
}

TEST(TestSort, SortFail){
  FILE* f = NULL;
  fopen_s(&f, "g_test.txt", "r");
  word_t* first = SortWords(Initialize(f));
  fclose(f);
  EXPECT_TRUE(!strcmp(first->word, "0123456789"));
  EXPECT_TRUE(!strcmp(first->next->word, "9876543210"));
}

//TEST()

///////////////////Тело функции///////////////////
/////////////////////////////////////////////////
int main(int argc, char** argv) {
  word_t* first = NULL;
  FILE* f;
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  fopen_s(&f, "test.txt", "r");
  if (f == NULL)
    return FILE_NOT_FOUND;
  first = Initialize(f);                //1
  printf("\n              We had:\n");
  PrintWords(first);                    //2
  first = SortWords(first);             //3
  printf("\n              We got:\n");
  PrintWords(first);
  MemoryFree(first);


  fclose(f);

  return 0;
}