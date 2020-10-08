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
	list_p* list = NULL;
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

TEST(TestSort_ZeroElements, EmptyList_ReturnNULL) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp3.txt", "r");
	list = CreateList(f);
	list = Sort(list);
	EXPECT_TRUE(list == NULL);
	fclose(f);
}

TEST(TestSort_OneElement, List_ReturnElement) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp1.txt", "r");
	list = CreateList(f);
	list = Sort(list);
	EXPECT_TRUE(list != NULL);
	EXPECT_TRUE(list->next == NULL);
	fclose(f);
}

TEST(TestSort_ThreeElements, ListDifferent_ReturnRightsequence) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p)), * tmp = (list_p*)malloc(sizeof(list_p)), * dop = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp4.txt", "r");
	list = CreateList(f);
	list = Sort(list);
	tmp = list->next;
	dop = tmp->next;
	EXPECT_TRUE(list->T < tmp->T);
	EXPECT_TRUE(tmp->T < dop->T);
	printf("\n");
	fclose(f);
}

TEST(TestSort_ThreeElements, ListEqualtemp_ReturnRightsequence) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p)), * tmp = (list_p*)malloc(sizeof(list_p)), * dop = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp5.txt", "r");
	list = CreateList(f);
	list = Sort(list);
	tmp = list->next;
	dop = tmp->next;
	EXPECT_TRUE(list->day < tmp->day);
	EXPECT_TRUE(tmp->year < dop->year);
	printf("\n");
	fclose(f);
}

TEST(TestSort_ThreeElements, ListEqualElements_ReturnRightsequence) {
	FILE* f;
	list_p* list = (list_p*)malloc(sizeof(list_p)), * tmp = (list_p*)malloc(sizeof(list_p)),*dop = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp6.txt", "r");
	list = CreateList(f);
	list = Sort(list);
	tmp = list->next;
	dop = tmp->next;
	EXPECT_TRUE(list->T == tmp->T);
	EXPECT_TRUE(list->day == tmp->day);
	EXPECT_TRUE(list->month == tmp->month);
	EXPECT_TRUE(list->year == tmp->year);

	printf("\n");

	EXPECT_TRUE(list->T == dop->T);
	EXPECT_TRUE(list->day == dop->day);
	EXPECT_TRUE(list->month == dop->month);
	EXPECT_TRUE(list->year == dop->year);

	printf("\n");

	EXPECT_TRUE(dop->T == tmp->T);
	EXPECT_TRUE(dop->day == tmp->day);
	EXPECT_TRUE(dop->month == tmp->month);
	EXPECT_TRUE(dop->year == tmp->year);

	printf("\n");
	EXPECT_TRUE(list != NULL);
	EXPECT_TRUE(tmp != NULL);
	EXPECT_TRUE(dop != NULL);
	fclose(f);
}

TEST(Test_Temp, ReturnRightTemp) {
	FILE* f;
	int t = 0, fl = 0;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	f = fopen("temp.txt", "r");
	list = CreateList(f);
	printf("write temperature you need to find\n");
	scanf_s("%d", &t);
	fl = FindTemp(list, t, fl);
	EXPECT_TRUE(fl == t);
	fclose(f);
}

