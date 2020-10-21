#include "pch.h"
#include "Functions.c"
//21 variant

TEST(AddElementToListTest, nullptrWord_errcode_2) {

  LST* list = NULL;
  int err;

  err = AddElementToList(&list, 1, NULL);

  EXPECT_EQ(err, 2);
}

TEST(AddElementToListTest, addingNewElement)
{
  LST* list = NULL;
  AddElementToList(&list, 10, "word");
  EXPECT_EQ(list->keyDigit,10);
  EXPECT_TRUE(!strcmp(list->word, "word"));
}

TEST(AddElementToListTest, sort)
{
  LST* list = NULL;

  AddElementToList(&list, 4, "4");
  AddElementToList(&list, 2, "2");
  AddElementToList(&list, 3, "3");

  EXPECT_TRUE(list->keyDigit < list->ptrToNext->keyDigit);
  EXPECT_TRUE(list->ptrToNext->keyDigit < list->ptrToNext->ptrToNext->keyDigit);
}

TEST(AddElementToListTest, sameKeyCodes_expect_errcode_3)
{
  LST* list = NULL;
  int err;

  AddElementToList(&list, 1, "1");

  err = AddElementToList(&list, 1, "2");

  EXPECT_EQ(err,MATCH_OF_KEY_NUMBERS);
}

TEST(FindElementInListTest, notExistingElement_expect_0)
{
  LST list, list2;
  int output;
  list.keyDigit = 1;
  list.word[0] = 0;
  list.ptrToNext = &list2;
  list2.keyDigit = 2;
  list2.word[0] = 0;
  list2.ptrToNext = &list2;
  output = FindElementInList(&list, 3);
  EXPECT_EQ(output,0);
}

TEST(FindElementInListTest, existingElement_expect_1)
{
  LST list, list2;
  int output;
  list.keyDigit = 1;
  list.word[0] = 0;
  list.ptrToNext = &list2;
  list2.keyDigit = 2;
  list2.word[0] = 0;
  list2.ptrToNext = &list2;
  output = FindElementInList(&list, 2);
  EXPECT_EQ(output, 1);
  output = FindElementInList(&list, 1);
  EXPECT_EQ(output, 1);
}

int main(int argc,char**argv)
{
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  LST* list = NULL;
  char inputFileName[261] = "D:\\folders\\Desktop\\123.txt";//путь к файлу с входными данными

  int err = ReadFromFileToList(&list, inputFileName);

  if (err)
  {
    switch (err)
    {
    case NOT_ENOUGH_MEMORY:
      printf("not enough memory!");
      break;
    case NULLPTR_STRING_ON_INPUT:
      printf("not correct input format");
      break;
    case MATCH_OF_KEY_NUMBERS:
      printf("keycodes match");
      break;
    case FILE_CANNOT_BE_OPENED:
      printf("file cannot be opened");
      break;

    }
    system("pause");
    return -1;
  }

  int key = 3;
  printf("there %s element with keycode %d in the list\n", FindElementInList(list, key) ? "is an" : "is not", key);
  PrintList(list);
  DeleteList(list);
  system("pause");
  return 0;
}