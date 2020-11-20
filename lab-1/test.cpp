#include "pch.h"
extern"C" {
#include"list.h"
}


TEST(InsertStrToList, InsertStrToList_Long_str) {
	char word[] = { "test " };
	list_t* p = InsertStrToList(word);
	EXPECT_STREQ(p->str, "test ");
}

TEST(InsertTextToList, InsertTextToList_n_0) {
	char s[][maxLength] = { "a", "b", "c" };
	int n = 0;
	ASSERT_EQ(NULL, InsertTextToList(s, n));
}

TEST(InsertTextToList, InsertTextToList_n_1) {
	char s[][maxLength] = { "odna strochka" };
	int n = sizeof(s) / maxLength * sizeof(char);
	ASSERT_TRUE(InsertTextToList(s, n) != NULL);
}

TEST(InsertTextToList, InsertTextToList_str_maxLengtn) {
	char s[][maxLength] = { "looooooooooong", "b", "c", "d", "e", "f","g", "h", "i","g","k", "l", "m", "n", "o" , "t", "4" };
	int n = sizeof(s) / maxLength * sizeof(char);
	ASSERT_TRUE(InsertTextToList(s, n) != NULL);
}

TEST(Merge, Merge_good_str) {
	char s[][maxLength] = { "my ", "test" };
	int n = sizeof(s) / maxLength * sizeof(char);
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list_t* p = (list_t*)malloc(sizeof(list_t));
	list_t* p1 = (list_t*)malloc(sizeof(list_t));
	p->str = "my ";
	p1->str = "test";
	list = p;
	p->next = p1;
	p1->next = NULL;
	char* arr = Merge(list, n);

	EXPECT_STREQ(arr, "my test");

	ListDestroy(list);
}

TEST(Length, Length_n_0) {
	char s[][maxLength] = { "a", "b", "c" };
	int n = 0;
	ASSERT_EQ(0, Length(s, n));
}

TEST(Length, Length_empty_str) {
	char s[][maxLength] = { "" };
	int n = sizeof(s) / maxLength * sizeof(char);
	ASSERT_EQ(0, Length(s, n));
}

TEST(Length, Length_all_is_well) {
	char s[][maxLength] = { "tut ", "dolzna byt ", "pashalka" };
	int n = sizeof(s) / maxLength * sizeof(char);
	ASSERT_EQ(23, Length(s, n));

}

TEST(Merge, Merge_null) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list = NULL;

	char* arr = Merge(list, 15);

	EXPECT_TRUE(arr == NULL);

	free(list);
}

