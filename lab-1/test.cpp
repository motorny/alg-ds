#include "pch.h"
#include "C:/Users/semen/source/repos/Project1/Project1/func.c"

TEST(write, normal) {
	FILE* fp = fopen("test1.txt", "r");
	LIST* Test = (LIST*)malloc(sizeof(LIST));
	write(fp, Test);
	ASSERT_EQ(strcmp(Test->data, "arbuz\n"), 0);
	ASSERT_EQ(strcmp(Test->next->data, "banan\n"), 0);
    ASSERT_EQ(strcmp(Test->next->next->data, "coc\n"), 0);
	ASSERT_EQ(strcmp(Test->next->next->next->data, "prikol\n"), 0);
	free_list(Test);
}

TEST(write, EmptyFile) {
	FILE* fp2 = fopen("test2.txt", "r");
	LIST* Test2 = (LIST*)malloc(sizeof(LIST));
	write(fp2, Test2);
	ASSERT_EQ(Test2->data[0], '\0');
	free_list(Test2);
}

TEST(write, SameStr) {
	FILE* fp = fopen("test3.txt", "r");
	LIST* Test = (LIST*)malloc(sizeof(LIST));
	write(fp, Test);
	ASSERT_EQ(strcmp(Test->data, "afas\n"), 0);
	ASSERT_EQ(strcmp(Test->next->data, "afas\n"), 0);
	ASSERT_EQ(strcmp(Test->next->next->data, "gdsg\n"), 0);
	ASSERT_EQ(strcmp(Test->next->next->next->data, "gdsg\n"), 0);
	ASSERT_EQ(strcmp(Test->next->next->next->next->data, "gdsh\n"), 0);
	ASSERT_EQ(strcmp(Test->next->next->next->next->next->data, "tew\n"), 0);
	free_list(Test);
}

TEST(merge, normal) {
	LIST* Test1 = (LIST*)malloc(sizeof(LIST));
	LIST* Test2 = (LIST*)malloc(sizeof(LIST));
	LIST* Test3 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock1 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock2 = (LIST*)malloc(sizeof(LIST)); 
	LIST* NewBlock3 = (LIST*)malloc(sizeof(LIST));
	strcpy(Test1->data, "acd\n");
	Test1->next = NewBlock1;
	strcpy(NewBlock1->data, "dog\n");
	NewBlock1->next = NewBlock2;
	strcpy(NewBlock2->data, "kis\n");
	NewBlock2->next = NULL;
	strcpy(Test2->data, "abc\n");
	Test2->next = NewBlock3;
	strcpy(NewBlock3->data, "bad\n");
	NewBlock3->next = NULL;
	merger(Test1, Test2,Test3);
	ASSERT_EQ(strcmp(Test3->data,"abc\n"),0);
	ASSERT_EQ(strcmp(Test3->next->data, "acd\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->data, "bad\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->next->data, "dog\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->next->next->data, "kis\n"), 0);
	free_list(Test1);
	free_list(Test2);
	free_list(Test3);
}

TEST(merge, EmptyList1) {
	LIST* Test1 = (LIST*)malloc(sizeof(LIST));
	LIST* Test3 = (LIST*)malloc(sizeof(LIST));
	LIST* Test2 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
	Test1->data[0] = '\0';
	Test1->next = NULL;
	strcpy(Test2->data, "abc\n");
	Test2->next = NewBlock;
	strcpy(NewBlock->data, "kis\n");
	NewBlock->next = NULL;
	merger(Test1, Test2,Test3);
	ASSERT_EQ(strcmp(Test3->data, "abc\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->data, "kis\n"), 0);
	free_list(Test1);
	free_list(Test2);
	free_list(Test3);
}

TEST(merge, EmptyList2) {
	LIST* Test1 = (LIST*)malloc(sizeof(LIST));
	LIST* Test2 = (LIST*)malloc(sizeof(LIST));
	LIST* Test3 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock = (LIST*)malloc(sizeof(LIST));
	Test2->data[0] = '\0';
	Test2->next = NULL;
	strcpy(Test1->data, "abc\n");
	Test1->next = NewBlock;
	strcpy(NewBlock->data, "kis\n");
	NewBlock->next = NULL;
	merger(Test1, Test2, Test3);
	ASSERT_EQ(strcmp(Test3->data, "abc\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->data, "kis\n"), 0);
	free_list(Test1);
	free_list(Test2);
	free_list(Test3);
}

TEST(merge, EmptyList1AndList2) {
	LIST* Test1 = (LIST*)malloc(sizeof(LIST));
	LIST* Test2 = (LIST*)malloc(sizeof(LIST));
	LIST* Test3 = (LIST*)malloc(sizeof(LIST));
	Test1->data[0] = '\0';
	Test1->next = NULL;
	Test2->data[0] = '\0';
	Test2->next = NULL;
	merger(Test1, Test2, Test3);
	ASSERT_EQ(Test3->data[0], '\0');
	free_list(Test1);
	free_list(Test2);
	free_list(Test3);
}

TEST(merge, SameStr) {
	LIST* Test1 = (LIST*)malloc(sizeof(LIST));
	LIST* Test2 = (LIST*)malloc(sizeof(LIST));
	LIST* Test3 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock1 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock2 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock3 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock4 = (LIST*)malloc(sizeof(LIST));
	LIST* NewBlock5 = (LIST*)malloc(sizeof(LIST));
	strcpy(Test1->data, "afas\n");
	Test1->next = NewBlock1;
	strcpy(NewBlock1->data, "gdsg\n");
	NewBlock1->next = NewBlock2;
	strcpy(NewBlock2->data, "gdsh\n");
	NewBlock2->next = NewBlock4;
	strcpy(NewBlock4->data, "tew\n");
	NewBlock4->next = NULL;
	strcpy(Test2->data, "afas\n");
	Test2->next = NewBlock3;
	strcpy(NewBlock3->data, "gdsh\n");
	NewBlock3->next = NewBlock5;
	strcpy(NewBlock5->data, "tew\n");
	NewBlock5->next = NULL;
	merger(Test1, Test2, Test3);
	ASSERT_EQ(strcmp(Test3->data, "afas\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->data, "afas\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->data, "gdsg\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->next->data, "gdsh\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->next->next->data, "gdsh\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->next->next->next->data, "tew\n"), 0);
	ASSERT_EQ(strcmp(Test3->next->next->next->next->next->next->data, "tew\n"), 0);
	free_list(Test1);
	free_list(Test2);
	free_list(Test3);
}

