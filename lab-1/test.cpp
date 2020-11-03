#include "pch.h"

extern "C" {
#include "..\LabA\concat_list.h"
#include "..\LabA\concatenation.c"
}

#define STRING_LENGTH 10

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

char string1[STRING_LENGTH] = { "let's " };
char string2[STRING_LENGTH] = { "test " };
char string3[STRING_LENGTH] = { "it" };

list_t* InitList() {
	error_t error;
	list_t* list = (list_t*)malloc(sizeof(list_t));
	Push(string1, list, &error);
	Push(string2, list, &error);
	Push(string3, list, &error);

	return list;
}

TEST(Concat, ConcatStrings) {
	list_t* list = InitList();
	error_t error;
	int len = strlen(string1) + strlen(string2) + strlen(string3);
	ASSERT_TRUE(list != NULL);
	char* arr = Concat(list, &len, &error);

	EXPECT_STREQ(arr, "let's test it");

	DestoyList(list, &error);
}

TEST(Concat, ConcatEmptyList) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	
	list->head = NULL;
	error_t error;
	int len = 0;

	char* arr = Concat(list, &len, &error);
	
	EXPECT_TRUE(arr == NULL);

	free(list);
}