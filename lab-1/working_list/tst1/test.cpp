#include "pch.h"
#include "gtest/gtest.h"
#include "..\working_list\working_list.h"


TEST(ConverInputToNode,InputEmptyReturnNull) {
	char* tmp = NULL;
	EXPECT_EQ(NULL, ConvertInputToNode(tmp));
}

TEST(ConverInputToNode, IncorrectInputFormatReturnNull) {
	char* tmp = (char*)calloc(MAX_LE * 3,sizeof(char));
	tmp = "T R";									// instead of "T  R" which would work just fine
	EXPECT_EQ(NULL, ConvertInputToNode(tmp));
	free(tmp);
}

TEST(ConverInputToNode, SurnameLengthExceedsMaximumReturnNull) {
	char* tmp = (char*)calloc(MAX_LE * 3, sizeof(char));
	tmp = "Tasdqwezxcvbnmsd Zxc Qwe";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_EQ(NULL, person);
	free(tmp);
	free(person);
}

TEST(ConverInputToNode, NameLengthExceedsMaximumReturnNull) {
	char* tmp = (char*)calloc(MAX_LE * 3, sizeof(char));
	tmp = "Zxc Tasdqwezxcvbnmsd Qwe";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_EQ(NULL, person);
	free(tmp);
	free(person);
}

TEST(ConverInputToNode, SecondNameLengthExceedsMaximumReturnNull) {
	char* tmp = (char*)calloc(MAX_LE * 3, sizeof(char));
	tmp = "Zxc Tasdqwezxcvbnmsd Qwe";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_EQ(NULL, person);
	free(tmp);
	free(person);
}


TEST(ConverInputToNode, CorrectSurnameRecordingReturnValidVal) {
	char* tmp = (char*)calloc(MAX_LE * 3, sizeof(char));
	tmp = "Zxc Qwe Tas";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_STREQ("Zxc", person->surname);
	free(tmp);
	free(person);
}
TEST(ConverInputToNode, CorrectNameRecordingReturnValidVal) {
	char* tmp = (char*)calloc(MAX_LE * 3, sizeof(char));
	tmp = "Zxc Qwe Tas";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_STREQ("Qwe", person->name);
	free(tmp);
	free(person);

}TEST(ConverInputToNode, CorrectSecondNameRecordingReturnValidVal) {
	char* tmp = (char*)calloc(MAX_LE * 3, sizeof(char));
	tmp = "Zxc Qwe Tas";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_STREQ("Tas", person->scndname);
	free(tmp);
	free(person);
}

TEST(GetPtrLast, EmptyListReturnNull) {
	tnode* top = NULL;
	EXPECT_EQ(NULL, GetPtrLast(top));
}

TEST(GetPtrLast, NonEmptyListReturnValidVal) {
	tnode second = { "R", "T", "Y", NULL };
	tnode top = {"Q", "W", "E", &second};
	tnode* result = GetPtrLast(&top);
	EXPECT_EQ(&second, result);
}


TEST(Compare, CompareWithEmptyElementFromListReturnNoMatch) {
	tnode* element = NULL;
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(EMPTY_ELEMENT, Compare(element,&info));
}

TEST(Compare, CompareWithEmptyInputReturnNoMatch) {
	tnode* info = NULL;
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(EMPTY_ELEMENT, Compare(&element, info));
}


TEST(Compare, CompareWithInputWithEmptySurnameReturnNoMatch) {
	tnode info = {"", "W", "E", NULL};
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptyNameReturnNoMatch) {
	tnode info = { "Q", "", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}


TEST(Compare, CompareWithInputWithEmptySecondnNameReturnNoMatch) {
	tnode info = { "Q", "W", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptySurname&NameReturnNoMatch) {
	tnode info = { "", "", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptySurname&SecondNameReturnNoMatch) {
	tnode info = { "", "W", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptyName&SecondNameReturnNoMatch) {
	tnode info = { "Q", "", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptyEverythingReturnNoMatch) {
	tnode info = { "", "", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(NO_MATCH, Compare(&element, &info));
}


TEST(Compare, CompareWithInputMatchingReturnMatch) {
	tnode info = { "Q", "W", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}

TEST(AddToList, EmptyInputReturnEmptyElement) {
	tnode* input = NULL;
	tnode* top = NULL;
	EXPECT_EQ(EMPTY_ELEMENT, AddToList(&top, input));
}


TEST(AddToList, EmptyListReturnValidVal) {
	tnode input = { "Q", "W", "E", NULL };
	tnode * top = NULL;
	AddToList(&top, &input);
	EXPECT_EQ(top, input);
}

TEST(AddToList, NonEmptyListReturnValidVal) {
	tnode input = { "R", "T", "Y", NULL };
	tnode elem = { "Q", "W", "E", NULL };
	tnode* top = &elem;
	AddToList(&top, &input);
	EXPECT_EQ(top->next, input);
}


TEST(PrintFilteredList, NoMatchesInListReturnZero) {
	tnode elem3 = { "R", "T", "Y", NULL };
	tnode elem2= { "Q", "W", "E", &elem3 };
	tnode elem1 = { "Z", "X", "C", &elem2 };
	tnode input = { "M", "", "C", NULL };
	tnode* top = &elem1;
	int count = PrintFilteredList(&top, &input);
	EXPECT_EQ(0, count);
}


TEST(PrintFilteredList, OneMatchInListReturnOne) {
	tnode elem3 = { "R", "T", "Y", NULL };
	tnode elem2 = { "Q", "W", "E", &elem3 };
	tnode elem1 = { "Z", "X", "C", &elem2 };
	tnode input = { "Q", "W", "", NULL };
	tnode* top = &elem1;
	int count = PrintFilteredList(&top, &input);
	EXPECT_EQ(1, count);
}
