#include "pch.h"
extern"C" {
#include"list.h"
}


TEST(InsertNode, return_good_str) {
	char word[] = { "test" };
	list_t* p = InsertNode(word);
	EXPECT_STREQ(p->str, "test");
}


TEST(Merge, Merge_good_str) {
	char s[][maxLength] = { "my ", "test" };
	int n = sizeof(s) / maxLength * sizeof(char);
	list_t* list = Insert(s, n);
	ASSERT_TRUE(list != NULL);
	char* arr = Merge(list, n);

	EXPECT_STREQ(arr, "my test");

	ListDestroy(list);
}

TEST(Merge, Merge_null) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list = NULL;

	char* arr = Merge(list,15);

	EXPECT_TRUE(arr == NULL);

	free(list);
}