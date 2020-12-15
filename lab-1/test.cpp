#include "pch.h"

extern "C" {
#include "OperationsWithList.h"
}


TEST(TransformToList, CorrectRecordings) {
	char tmp[] = "Pushkin Alex Sergeevich";
	List* person = TransformToList(tmp);

	EXPECT_STREQ("Pushkin", person->surname);
	EXPECT_STREQ("Alex", person->name);
	EXPECT_STREQ("Sergeevich", person->father);
}



TEST(Compare, CompareWithEmptySurnameReturnSAME) {
	List request = { "", "N", "F", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}

TEST(Compare, CompareWithEmptyNameReturnSAME) {
	List request = { "S", "", "F", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}

TEST(Compare, CompareWithEmptyFatherReturnSAME) {
	List request = { "S", "N", "", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}

TEST(Compare, CompareWithEmptyNameAndFatherReturnSAME) {
	List request = { "S", "", "", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}

TEST(Compare, CompareWithEmptySurnameAndFatherReturnSAME) {
	List request = { "", "N", "", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}

TEST(Compare, CompareWithEmptySurnameAndNameReturnSAME) {
	List request = { "", "", "F", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}

TEST(Compare, CompareWithInputWithEverythingFilledReturnSAME) {
	List request = { "S", "N", "F", NULL };
	List man = { "Surname", "Name", "Father", NULL };

	EXPECT_EQ(SAME, Compare(&man, &request));
}



TEST(GetStr, CorrectRecording) {
	char surname[] = "Pushkin", name[SIZE] = "Alex", father[] = "Sergeevich";
	List* man = (List*)malloc(sizeof(List));

	GetStr(man, surname, name, father);
	EXPECT_STREQ("Pushkin", man->surname);
	EXPECT_STREQ("Alex", man->name);
	EXPECT_STREQ("Sergeevich", man->father);
}



TEST(AddToList, SortBySurameReturnCorrectTop) {
	List input = { "Aa", "Aa", "Aa", NULL }; 
	List man = { "Bb", "Bb", "Bb", NULL }; 
	List* top = &man;

	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}

TEST(AddToList, SortByNameReturnCorrectTop) {
	List input = { "Bb", "Aa", "Aa", NULL };
	List man = { "Bb", "Bb", "Bb", NULL };
	List* top = &man;

	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}

TEST(AddToList, SortByFatherReturnCorrectTop) {
	List input = { "Bb", "Bb", "Aa", NULL };
	List man = { "Bb", "Bb", "Bb", NULL };
	List* top = &man;

	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}

TEST(AddToList, SortBySurameReturnCorrectEnd) {
	List man = { "Aa", "Aa", "Aa", NULL };
	List input = { "Bb", "Bb", "Bb", NULL };
	List* top = &man;

	AddToList(&top, &input);
	EXPECT_EQ(top, &man);
}

TEST(AddToList, SortByNameReturnCorrectEnd) {
	List man = { "Bb", "Aa", "Aa", NULL };
	List input = { "Bb", "Bb", "Bb", NULL };
	List* top = &man;

	AddToList(&top, &input);
	EXPECT_EQ(top, &man);
}

TEST(AddToList, SortByFatherReturnCorrectEnd) {
	List man = { "Bb", "Bb", "Aa", NULL };
	List input = { "Bb", "Bb", "Bb", NULL };
	List* top = &man;

	AddToList(&top, &input);
	EXPECT_EQ(top, &man);
}