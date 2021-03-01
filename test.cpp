#include "pch.h"
#include "vertex.h"


TEST(CombineNULLptr, returnNULL) {
	EXPECT_TRUE(combine(NULL, NULL) == NULL);
}

TEST(combineGoodptr, returnPtr) {
	vertex* t1 = getFork(1), * t2 = getFork(2), * t3 = NULL;
	EXPECT_TRUE((t3 = combine(t1, t2)) != NULL);
	wreck(t3);
}

TEST(partNULLptr, ptrisNull) {
	vertex* t1, * t2, * t = NULL;
	parted(t, 1, &t1, &t2);
	EXPECT_TRUE((t1 && t2) == NULL);
}

TEST(partGoodptr, ptrisntNull) {
	vertex* t1, * t2, * t = NULL;
	sum(&t, 1);
	sum(&t, 2);
	sum(&t, 3);
	parted(t, 2, &t1, &t2);
	EXPECT_TRUE((t1 && t2) != NULL);
	wreck(t1);
	wreck(t2);
}

TEST(findNotFound, return0) {
	vertex* t = NULL;
	sum(&t, 1);
	EXPECT_EQ(uncover(t, 2), 0);
	wreck(t);
}

TEST(findFound, return1) {
	vertex* t = NULL;
	sum(&t, 1);
	EXPECT_EQ(uncover(t, 1), 1);
	wreck(t);
}

TEST(sumElem, ptrisvalid) {
	vertex* t = NULL;
	sum(&t, 1);
	EXPECT_TRUE(t != NULL);
	wreck(t);
}

TEST(ersItmNoItm, return0) {
	vertex* t = NULL;
	sum(&t, 1);
	EXPECT_EQ(eraseItm(&t, 2), 0);
	wreck(t);
}

TEST(ersItmgoodItm, return1) {
	vertex* t = NULL;
	sum(&t, 1);
	sum(&t, 2);
	EXPECT_EQ(eraseItm(&t, 2), 1);
	wreck(t);
}