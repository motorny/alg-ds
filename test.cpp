#include "pch.h"

extern "C"
{
#include "labH.h"
}

TEST(MergeNull, ReturnNull) {
	treap* left = NULL;
	treap* right = NULL;

	EXPECT_EQ(Merge(left, right), nullptr);
}

TEST(SplitNULL, EmptyTree_ReturnNullPtrs) {
	treap* tree, * left, * right; 
	tree = left = right = NULL;
	Split(tree, 1, &left, &right);

	EXPECT_EQ(left, nullptr);
	EXPECT_EQ(right, nullptr);
}

TEST(MergeValid, ReturnPtr) {
	treap* left = (treap*)malloc(sizeof(treap));

	EXPECT_NE(left, nullptr);
	treap* right = (treap*)malloc(sizeof(treap));
	treap* tree = NULL;

	EXPECT_NE(right, nullptr);
	left->left = left->right = right->left = right->right = NULL;
	left->key = 1;
	right->key = 3;
	left->priority = rand();
	right->priority = rand();
	tree = Merge(left, right);

	EXPECT_NE(tree, nullptr);
}

TEST(SplitValid, ReturnPtr) {
	treap* t1, * t2, * t;
	t1 = t2 = t = NULL;
	Add(&t, 1);
	Add(&t, 5);
	Add(&t, 10);
	Split(t, 5, &t1, &t2);

	EXPECT_NE(t1, nullptr);
	EXPECT_NE(t2, nullptr);
	TreapOff(t1);
	TreapOff(t2);
}

TEST(AddValid, ReturnPtr) {
	treap* t = NULL;
	Add(&t, 5);
	EXPECT_NE(t, nullptr);
	TreapOff(t);
}

TEST(NotFound, ReturnNo) {
	treap* t = NULL;
	Add(&t, 1);
	int f = Find(t, 5);
	EXPECT_EQ(f, NOTFOUND);
	TreapOff(t);
}

TEST(Found, ReturnYes) {
	treap* t = NULL;
	Add(&t, 1);
	int f = Find(t, 1);
	EXPECT_EQ(f, FOUND);
	TreapOff(t);
}
