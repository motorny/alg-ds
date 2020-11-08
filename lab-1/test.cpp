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


TEST(Concat, ConcatStrings) {

	char string1[STRING_LENGTH] = { "let's " };
	char string2[STRING_LENGTH] = { "test " };
	char string3[STRING_LENGTH] = { "it" };
	list_t* list = (list_t*)malloc(sizeof(list_t));
	if (list) {
		list->tail = (node_t*)malloc(sizeof(node_t));
		if (list->tail) {
			list->head = list->tail;
			list->tail->data = string1;
			list->tail->next = NULL;
		}
		list->tail->next = (node_t*)malloc(sizeof(node_t));
		if (list->tail->next) {
			list->tail = list->tail->next;
			list->tail->data = string2;
			list->tail->next = NULL;
		}
		list->tail->next = (node_t*)malloc(sizeof(node_t));
		if (list->tail->next) {
			list->tail = list->tail->next;
			list->tail->data = string3;
			list->tail->next = NULL;
		}
	}
	error_t error;
	int len = strlen(string1) + strlen(string2) + strlen(string3);		
	ASSERT_TRUE(list != NULL);

	char* arr = Concat(list, &len, &error);
	printf("%s", arr);

	EXPECT_STREQ(arr, "let's test it");

	node_t* reserve = list->head;
	while (reserve->next) {
		list->head = reserve->next;
		free(reserve);
		reserve = list->head;
	}
	free(reserve);
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

TEST(Push, PushNullList_returnMYFAIL){
	list_t* list = NULL;
	error_t error;
	char string1[STRING_LENGTH] = { "let's " };

	ASSERT_EQ(MYFAIL, Push(string1, list, &error));
}

TEST(Push, PushOkay_returnMYSUCCESS) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->head = NULL;
	list->tail = NULL;
	error_t error;
	char string1[STRING_LENGTH] = { "let's " };

	ASSERT_EQ(MYSUCCESS, Push(string1, list, &error));

	free(list->tail);
	free(list);
}