#include "pch.h"
extern "C" {
#include "../Laba_1_26/Header.h"
}


TEST(TestCreate_OneElemPositive, OneElem_ReturnPosVal) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp1.txt", "r");
	list = CreateList(f);
	EXPECT_TRUE(list->T > 0);
	fclose(f);
}

TEST(TestCreate_OneElemNegative, OneElem_ReturnNegVal) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp2.txt", "r");
	list = CreateList(f);
	EXPECT_TRUE(list->T < 0);
	fclose(f);
}

TEST(TestCreate_EmptyList, Emptylist_ReturnNull) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp3.txt", "r");
	list = CreateList(f);
	EXPECT_TRUE(list == NULL);
	fclose(f);
}

TEST(TestCreate_ThreeElements, ThreeElem_ElemNoNull) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp4.txt", "r");
	list = CreateList(f);
	EXPECT_FALSE(list == NULL);
	list = list->next;
	EXPECT_FALSE(list == NULL);
	list = list->next;
	EXPECT_FALSE(list == NULL);
	EXPECT_TRUE(list->next == NULL);
	fclose(f);
}

TEST(TestDestroy_ZeroElements, EmptyList_ReturnNULL) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp3.txt", "r");
	list = CreateList(f);
	list = Destroy(list);
	EXPECT_TRUE(list == NULL);
	fclose(f);
}

TEST(TestDestroy_OneElement, List_ReturnNULL) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp1.txt", "r");
	list = CreateList(f);
	list = Destroy(list);
	EXPECT_TRUE(list == NULL);
	fclose(f);
}

TEST(TestDestroy_ThreeElements, List_ReturnNULL) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp4.txt", "r");
	list = CreateList(f);
	list = Destroy(list);
	EXPECT_TRUE(list == NULL);
	fclose(f);
}

TEST(TestAdd_OneElement, List_ReturnRightList) {
	FILE* f, * g;
	list_p* list = (list_p*)malloc(sizeof(list_p)), * head = (list_p*)malloc(sizeof(list_p));
	char str[50];
	f = fopen("temp4.txt", "r");
	g = fopen("temp1.txt", "r");
	fgets(str, sizeof(str), g);
	list = CreateList(f);
	head = list;
	list = Add(head, str, list);
	EXPECT_TRUE(list->T == -66);
	list = list->next;
	EXPECT_TRUE(list->T == 2);
	list = list->next;
	EXPECT_TRUE(list->T == 6);
	list = list->next;
	EXPECT_TRUE(list->T == 49);
	list = list->next;
	fclose(f);
	fclose(g);
}

TEST(TestAdd_ThreeElements, List_ReturnRightList) {
	FILE* f, * g;
	list_p* list = (list_p*)malloc(sizeof(list_p)), * head = (list_p*)malloc(sizeof(list_p));
	char str[50];
	char* a;
	int n = 0;
	f = fopen("temp1.txt", "r");
	g = fopen("temp4.txt", "r");
	list = CreateList(f);
	head = list;
	while (1) {
		n++;
		a = fgets(str, sizeof(str), g);
		if (a == NULL || a == "\n") {
			if (n == 1) {
				list = NULL;
				break;
			}
			else
				break;
		}
		list = Add(head, str, list);
		head = list;
	}
	EXPECT_TRUE(list->T == -66);
	list = list->next;
	EXPECT_TRUE(list->T == 2);
	list = list->next;
	EXPECT_TRUE(list->T == 6);
	list = list->next;
	EXPECT_TRUE(list->T == 49);
	list = list->next;
	fclose(f);
	fclose(g);
}

TEST(TestAdd_ZeroElements, List_ReturnRightList) {
	FILE* f, * g;
	list_p* list = (list_p*)malloc(sizeof(list_p)), * head = (list_p*)malloc(sizeof(list_p));
	char str[50];
	char* a;
	f = fopen("temp1.txt", "r");
	g = fopen("temp3.txt", "r");
	list = CreateList(f);
	head = list;
	a = fgets(str, sizeof(str), g);
	if (a == NULL || a == "\n")
		str[0] = '\n';

	list = Add(head, str, list);
	EXPECT_TRUE(list->T == 49);
	list = list->next;
	EXPECT_TRUE(list == NULL);
	fclose(f);
	fclose(g);
}

TEST(Test_Temp, ReturnRightTemp) {
	FILE* f;
	int t = 0, fl = 0;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp.txt", "r");
	list = CreateList(f);
	scanf_s("%d", &t);
	fl = FindTemp(list, t, fl);
	EXPECT_TRUE(fl == t);
	fclose(f);
}

