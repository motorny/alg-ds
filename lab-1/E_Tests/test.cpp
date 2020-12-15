#include "pch.h"

extern "C" {
#include "../Lab_4/Tree.h"
#include "../LAB_4/LAB_4.c"
}

TEST(IsItRightWidth, WhatWidth) {
	int n = 12467;
	n = WhatWidth(n);
	EXPECT_EQ(n, 5);
}

TEST(TwoElements, Addnode) {
	node_t* startnode;
	startnode = Addnode(1, 2);
	startnode = Addnode(2, 3);
	EXPECT_TRUE(startnode->right->key == 2);
	EXPECT_TRUE(startnode->left == NULL);
	DestroyTree(startnode);
}

TEST(IsitRightWidthAfterAdd, UpdateWidth) {
	node_t* startnode;
	int n = 0, m = 0;
	startnode = Addnode(4, 20);
	startnode = Addnode(2, 5);
	startnode = Addnode(1, 10);
	n = startnode->width;
	startnode = Addnode(3, 5);
	m = startnode->width;
	EXPECT_TRUE(m > n);
	DestroyTree(startnode);
}

TEST(FindElement, FindNode) {
	node_t* startnode;
	node_t* find;
	startnode = Addnode(4, 20);
	startnode = Addnode(2, 5);
	startnode = Addnode(1, 10);
	find = *FindNode(1);
	EXPECT_EQ(find, startnode->left->left);
	DestroyTree(startnode);
}
