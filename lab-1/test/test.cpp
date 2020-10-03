#include "pch.h"
#include "../Lab_1_3sem/listInit.c"

TEST(FuncTest, InitListTest) {
	myList* man = InitList("tSurname", "tName", "tPatron");
	ASSERT_TRUE(man != NULL);
	EXPECT_STREQ("tSurname", man->surname);
	EXPECT_STREQ("tName", man->name);
	EXPECT_STREQ("tPatron", man->patron);
	DeleteList(man);
	/*EXPECT_TRUE(true);*/
}

TEST(FuncTest, EnterSNPTest) {
	myList* man = InitList("", "", "");
	EnterSNP(man, "tSurname", "tName", "tPatron");
	EXPECT_STREQ("tSurname", man->surname);
	EXPECT_STREQ("tName", man->name);
	EXPECT_STREQ("tPatron", man->patron);
	DeleteList(man);
}


TEST(FuncTest, FindPosForManWith1ManTest) {
	enum SNP_E snp_pos = SURNAME;
	myList* nMan = NULL;
	myList* pMan = NULL;
	SNP snp;

	strcpy(snp.surname, "Aa");

	myList* man = InitList("tSurname", "tName", "tPatron");

	FindPosForMan(&man, snp, &pMan, &nMan, snp_pos);
	EXPECT_TRUE(pMan == NULL);
	EXPECT_TRUE(nMan == man);

	DeleteList(man);
}


TEST(FuncTest, AddManTest) {
	enum SNP_E snp_pos = SURNAME;
	myList *nextMan = NULL, *newMan = NULL;
	myList* pMan = NULL;

	SNP snp;

	strcpy(snp.surname, "Aa");
	strcpy(snp.name, "Aa");
	strcpy(snp.patron, "Aa");

	myList* man = InitList("tSurname", "tName", "tPatron");

	FindPosForMan(&man, snp, &pMan, &nextMan, snp_pos);
	newMan = AddMan(nextMan, pMan, snp.surname, snp.name, snp.patron);

	ASSERT_TRUE(newMan != NULL);
	EXPECT_TRUE((pMan == NULL) || (pMan->next == newMan));
	EXPECT_TRUE(newMan->next == nextMan);

	DeleteList(man);
}


TEST(FuncTest, Add2ListTestNoChangeOrder) {
	myList* start = NULL;
	myList* man1 = NULL, *man2 = NULL;
	SNP snp;
	
	strcpy(snp.surname, "Aa");
	strcpy(snp.name, "Aa");
	strcpy(snp.patron, "Aa");
	start = InitList(snp.surname, snp.name, snp.patron);
	man1 = start;

	strcpy(snp.surname, "Bb");
	strcpy(snp.name, "Bb");
	strcpy(snp.patron, "Bb");
	man2 = Add2List(&start, snp);

	ASSERT_TRUE(man1 != NULL);
	ASSERT_TRUE(man2 != NULL);
	EXPECT_TRUE(man1==start);
	EXPECT_TRUE(man1->next != NULL);
	EXPECT_TRUE(man2->next == NULL);

	DeleteList(start);
		
}

TEST(FuncTest, Add2ListTestWithChangeOrder) {
	myList* start = NULL;
	myList* man1 = NULL, * man2 = NULL;
	SNP snp;

	strcpy(snp.surname, "Bb");
	strcpy(snp.name, "Bb");
	strcpy(snp.patron, "Bb");
	start = InitList(snp.surname, snp.name, snp.patron);
	man1 = start;

	strcpy(snp.surname, "Aa");
	strcpy(snp.name, "Aa");
	strcpy(snp.patron, "Aa");
	man2 = Add2List(&start, snp);

	ASSERT_TRUE(man1 != NULL);
	ASSERT_TRUE(man2 != NULL);
	EXPECT_TRUE(man2 == start);
	EXPECT_TRUE(man2->next != NULL);
	EXPECT_TRUE(man1->next == NULL);
	
	DeleteList(start);

}

