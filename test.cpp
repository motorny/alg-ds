#include "pch.h"
extern "C" {
#include "treap.h"
}

TEST(MergeNULLpointer, returnNULL) {
  EXPECT_TRUE(merge(NULL, NULL) == NULL);
}

TEST(MergeGoodpointer, returnPtr) {
	treap* t1 = getNode(1), *t2 = getNode(2), *t3 = NULL;
	EXPECT_TRUE(( t3 = merge(t1, t2)) != NULL);
	destroy(t3);
}

TEST(splitNULLpointer, ptrisnull) {
	treap* t1, * t2, * t = NULL;
	split(t, 1, &t1, &t2);
	EXPECT_TRUE((t1 && t2) == NULL);
}

TEST(splitGoodpointer, ptrisntnull) {
	treap* t1, * t2, * t = NULL;
	add(&t, 1);
	add(&t, 2);
	add(&t, 3);
	split(t, 2, &t1, &t2);
	EXPECT_TRUE((t1 && t2) != NULL);
	destroy(t1);
	destroy(t2);
}

TEST(findNotFound, return0) {
	treap* t = NULL;
	add(&t, 1);
	EXPECT_EQ(find(t, 2), 0);
	destroy(t);
}

TEST(findFound, return1) {
	treap* t = NULL;
	add(&t, 1);
	EXPECT_EQ(find(t, 1), 1);
	destroy(t);
}

TEST(addElem, ptrisvalid) {
	treap* t = NULL;
	add(&t, 1);
	EXPECT_TRUE(t != NULL);
	destroy(t);
}

TEST(delElemNoelem, return0) {
	treap* t = NULL;
	add(&t, 1);
	EXPECT_EQ(delelem(&t, 2), 0);
	destroy(t);
}

TEST(delElemgoodlem, return1) {
	treap* t = NULL;
	add(&t, 1);
	add(&t, 2);
	EXPECT_EQ(delelem(&t, 2), 1);
	destroy(t);
}