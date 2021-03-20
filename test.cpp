#include "pch.h"
extern "C" {
#include"bptree.h"
}

TEST(Insert, elemExist) {
    BPtree* tree = init();
    insert(tree, 1);
    EXPECT_EQ(FALSE, insert(tree, 1));
    destroy(tree);
}

TEST(Insert, elemdoesntExist) {
    BPtree* tree = init();
    EXPECT_EQ(TRUE, insert(tree, 1));
    destroy(tree);
}

TEST(deleteEl, elemExist) {
	BPtree* tree = init();
	insert(tree, 1);
	EXPECT_EQ(TRUE, deleteEl(tree, 1));
	destroy(tree);
}

TEST(deleteEl, elemdoesntExist) {
	BPtree* tree = init();
	insert(tree, 1);
	EXPECT_EQ(FALSE, deleteEl(tree, 2));
	destroy(tree);
}

TEST(findEl, elemExist) {
	BPtree* tree = init();
	insert(tree, 1);
	EXPECT_EQ(TRUE, findEl(tree, 1));
	destroy(tree);
}

TEST(findEl, elemdoenstExist) {
	BPtree* tree = init();
	EXPECT_EQ(FALSE, findEl(tree, 1));
	destroy(tree);
}

TEST(insert, NULLptr) {
	BPtree* tree = NULL;
	EXPECT_EQ(FALSE, insert(tree, 1));
	destroy(tree);
}

TEST(insert, validPtr) {
	BPtree* tree = init();
	EXPECT_EQ(TRUE, insert(tree, 1));
	destroy(tree);
}