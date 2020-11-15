#include "pch.h"
#include "../Lab A/list.c"

TEST(findPlace, SameHours) {
	Node N1 = { "11.06.2011", "Ivanov A.", 24, NULL };
	Node N2 = { "11.05.2012", "Ivanov B.", 24, NULL };
	Node N3 = { "10.01.2001", "Ivanov G.", 24, NULL };
	Node N4 = { "14.10.2004", "Ivanov I.", 24, END_OF_LIST };
	N1.pPrev = &N2;
	N2.pPrev = &N3;
	N3.pPrev = &N4;

	Node newNode = { "11.06.2015", "Ivanov F.", 24, NULL };

	EXPECT_EQ(findPlace(&N1, &newNode), &N3);
}

TEST(findPlace, DifferentHours) {
	Node N1 = { "11.06.2011", "Ivanov A.", 39, NULL };
	Node N2 = { "11.05.2012", "Ivanov B.", 24, NULL };
	Node N3 = { "10.01.2001", "Ivanov G.", 11, NULL };
	Node N4 = { "14.10.2004", "Ivanov I.", 5, END_OF_LIST };
	N1.pPrev = &N2;
	N2.pPrev = &N3;
	N3.pPrev = &N4;

	Node newNode = { "11.06.2015", "Ivanov F.", 4, NULL };

	EXPECT_EQ(findPlace(&N1, &newNode), nullptr);
}

TEST(findLastNode, NullPointer) {
	EXPECT_EQ(findLastNode(NULL), nullptr);
}
TEST(findLastNode, OneNode) {
	Node N1 = { "11.06.2011", "Ivanov A.", 39, END_OF_LIST };
	EXPECT_EQ(findLastNode(&N1), &N1);
}

TEST(findLastNode, MoreThanOneNodes) {
	Node N1 = { "11.06.2011", "Ivanov A.", 39, NULL };
	Node N2 = { "11.05.2012", "Ivanov B.", 24, NULL };
	Node N3 = { "10.01.2001", "Ivanov G.", 11, NULL };
	Node N4 = { "14.10.2004", "Ivanov I.", 5, END_OF_LIST };
	N1.pPrev = &N2;
	N2.pPrev = &N3;
	N3.pPrev = &N4;

	EXPECT_EQ(findLastNode(&N1), &N4);
}