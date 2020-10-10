#include "pch.h"
#include "..\working_list\list_operations.c"



TEST(ConverInputToNode, InputEmptyReturnNull) {
	char* tmp = NULL;
	EXPECT_EQ(NULL, ConvertInputToNode(tmp));
}

TEST(ConverInputToNode, IncorrectInputFormatReturnNull) {
	char tmp[] = "T R";
	tnode* test = ConvertInputToNode(tmp);				// instead of "T  R" which would work just fine
	EXPECT_EQ(NULL, test);
}

TEST(ConverInputToNode, SurnameLengthExceedsMaximumReturnNull) {
	char txt[] = "Tasdqwezxcvbnmsd Zxc Qwe";
	tnode* person = ConvertInputToNode(txt);
	EXPECT_EQ(NULL, person);

}

TEST(ConverInputToNode, NameLengthExceedsMaximumReturnNull) {
	char tmp[] = "Zxc Tasdqwezxcvbnmsd Qwe";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_EQ(NULL, person);
}

TEST(ConverInputToNode, SecondNameLengthExceedsMaximumReturnNull) {
	char tmp[] = "Zxc Tasdqwezxcvbnmsd Qwe";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_EQ(NULL, person);

}


TEST(ConverInputToNode, CorrectSurnameRecordingReturnValidVal) {
	char tmp[]=  "Zxc Qwe Tas";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_STREQ("Zxc", person->surname);

}

TEST(ConverInputToNode, CorrectNameRecordingReturnValidVal) {
	char tmp[] = "Zxc Qwe Tas";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_STREQ("Qwe", person->name);
}

TEST (ConverInputToNode, CorrectSecondNameRecordingReturnValidVal) {
	char tmp[] = "Zxc Qwe Tas";
	tnode* person = ConvertInputToNode(tmp);
	EXPECT_STREQ("Tas", person->scndname);

}

TEST(GetPtrLast, EmptyListReturnNull) {
	tnode* top = NULL;
	EXPECT_EQ(NULL, GetPtrLast(top));
}

TEST(GetPtrLast, NonEmptyListReturnValidVal) {
	tnode second = { "R", "T", "Y", NULL };
	tnode top = { "Q", "W", "E", &second };
	tnode* result = GetPtrLast(&top);
	EXPECT_EQ(&second, result);
}


TEST(Compare, CompareWithEmptyElementFromListReturnNoMatch) {
	tnode* element = NULL;
	tnode info = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(EMPTY_ELEMENT, Compare(element, &info));
}


TEST(Compare, CompareWithEmptyInputReturnNoMatch) {
	tnode* info = NULL;
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(EMPTY_ELEMENT, Compare(&element, info));
}


TEST(Compare, CompareWithInputWithEmptySurnameReturnMatch) {
	tnode info = { "", "W", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptyNameReturnMatch) {
	tnode info = { "Q", "", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}


TEST(Compare, CompareWithInputWithEmptySecondnNameReturnMatch) {
	tnode info = { "Q", "W", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptyNameAndSecondNameReturnMatch) {
	tnode info = { "Q", "", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}

TEST(Compare, CompareWithInputWithEmptySurnameAndNameReturnMatch) {
	tnode info = { "", "", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}


TEST(Compare, CompareWithInputWithEmptyEverythingReturnMatch) {
	tnode info = { "", "", "", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}


TEST(Compare, CompareWithInputWithEverythingFilledReturnMatch) {
	tnode info = { "Q", "W", "E", NULL };
	tnode element = { "Qr", "Wt", "Ey", NULL };
	EXPECT_EQ(MATCH, Compare(&element, &info));
}

TEST(AddToList, EmptyInputEnteredReturnEmptyElement) {
	tnode* input = NULL;
	tnode* top = NULL;
	EXPECT_EQ(EMPTY_ELEMENT, AddToList(&top, input));
}


TEST(AddToList, AddToEmptyListReturnValidVal) {
	tnode input = { "Q", "W", "E", NULL };
	tnode * top = NULL;
	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}

TEST(AddToList, NonEmptyListReturnValidVal) {
	tnode input = { "R", "T", "Y", NULL };
	tnode elem = { "Q", "W", "E", NULL };
	tnode* top = &elem;
	AddToList(&top, &input);
	EXPECT_EQ(top->next, &input);
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
