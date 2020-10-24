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

TEST(AddToList, AddedNewLeastElementSortBySurnameReturnValidVal) {
	tnode input = { "Ab", "Cd", "Ef", NULL }; // should be new top elem
	tnode elem = { "Bb", "Zx", "Vb", NULL }; //present top elem
	tnode* top = &elem;
	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}

TEST(AddToList, AddedNewLeastElementSortByNameReturnValidVal) {
	tnode input = { "Ab", "Cd", "Ef", NULL }; // should be new top elem; surname equal,first by name
	tnode elem = { "Ab", "Zx", "Vb", NULL }; //present top elem
	tnode* top = &elem;
	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}
TEST(AddToList, AddedNewLeastElementSortByScndnameReturnValidVal) {
	tnode input = { "Ab", "Zx", "Af", NULL }; // should be new top elem, surname & name equal, first by scndname
	tnode elem = { "Bb", "Zx", "Vb", NULL }; //present top elem
	tnode* top = &elem;
	AddToList(&top, &input);
	EXPECT_EQ(top, &input);
}


TEST(AddToList, AddedNewElementToEndSortBySurnameOneElementListReturnValidVal) {
	tnode input = { "Tv", "Mf", "Rt", NULL };
	tnode elem = { "Bb", "Ax", "Vb", NULL };
	tnode* top = &elem;
	EXPECT_EQ(AddToList(&top, &input), ADD_TO_END);
}

TEST(AddToList, AddedNewElementToEndSortByNameOneElementListReturnValidVal) {
	tnode input = { "Bb", "Mf", "Rt", NULL }; 
	tnode elem = { "Bb", "Ax", "Vb", NULL }; 
	tnode* top = &elem;
	EXPECT_EQ(AddToList(&top, &input), ADD_TO_END);

}
TEST(AddToList, AddedNewElementToEndSortByScndnameOneElementListReturnValidVal) {
	tnode input = { "Bb", "Zx", "Zt", NULL };
	tnode elem = { "Bb", "Zx", "Vb", NULL };
	tnode* top = &elem;
	EXPECT_EQ(AddToList(&top, &input), ADD_TO_END);
}


TEST(AddToList, AddedNewElementToEndSortBySurnameManyElementListReturnValidVal) {
	tnode input = { "Tv", "Mf", "Rt", NULL };
	tnode elem2 = { "Bb", "Cx", "Tb", NULL };
	tnode elem1 = { "Ab", "Ax", "Vb", &elem2 };
	tnode* top = &elem1;
	EXPECT_EQ(AddToList(&top, &input), ADD_TO_END);
}


TEST (AddToList, AddedNewElementToEndSortByNameManyElementListReturnValidVal) {
	tnode input = { "Bb", "Mf", "Rt", NULL };
	tnode elem2 = { "Bb", "Cx", "Tb", NULL };
	tnode elem1 = { "Ab", "Ax", "Vb", &elem2 };
	tnode* top = &elem1;
	EXPECT_EQ(AddToList(&top, &input), ADD_TO_END);
}


TEST(AddToList, AddedNewElementToEndSortByScndnameManyElementListReturnValidVal) {
	tnode input = { "Bb", "Cx", "Zt", NULL };
	tnode elem2 = { "Bb", "Cx", "Tb", NULL };
	tnode elem1 = { "Ab", "Ax", "Vb", &elem2 };
	tnode* top = &elem1;
	EXPECT_EQ(AddToList(&top, &input), ADD_TO_END);
}


TEST(AddToList, AddedNewElementNotFirstOrLastSortBySurnameReturnValidVal) {
	tnode input = { "Bw", "Cd", "Ef", NULL }; 
	tnode elem2 = { "Cb", "Zx", "Vb", NULL };
	tnode elem1 = { "Ab", "Vt", "Nm", &elem2 };
	tnode* top = &elem1;
	AddToList(&top, &input);
	EXPECT_EQ(top->next, &input);
}



TEST(AddToList, AddedNewElementNotFirstOrLastSortByNameReturnValidVal) {
	tnode input = { "Cb", "Cd", "Ef", NULL };
	tnode elem2 = { "Cb", "Zx", "Vb", NULL };
	tnode elem1 = { "Ab", "Vt", "Nm", &elem2 };
	tnode* top = &elem1;
	AddToList(&top, &input);
	EXPECT_EQ(top->next, &input);
}

TEST(AddToList, AddedNewElementNotFirstOrLastSortByScndNameReturnValidVal) {
	tnode input = { "Cb", "Wd", "Af", NULL };
	tnode elem2 = { "Cb", "Wd", "Mb", NULL };
	tnode elem1 = { "Ab", "Vt", "Nm", &elem2 };
	tnode* top = &elem1;
	AddToList(&top, &input);
	EXPECT_EQ(top->next, &input);
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
