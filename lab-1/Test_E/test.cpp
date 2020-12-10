#include "pch.h"

extern "C" {
#include "..//Laba_E/Header.h"
}

TEST(GetWidth_number, Rightlen) {
	int n = 100;
	n = Getwidth(n);
	EXPECT_EQ(n, 3);
}

TEST(Add_TwoElems, RightPlace) {
	node_t* startnode;
	startnode = Addnode(1, 7);
	startnode = Addnode(2, 8);
	EXPECT_TRUE(startnode->left == NULL);
	EXPECT_TRUE(startnode->right->key == 2);
	DestroyTree(startnode);
}

TEST(Destroy_Elem, Rightree) {
	node_t* start;
	start = Addnode(5, 3);
	start = Addnode(3, 8);
	start = Addnode(8, 9);
	Deletenode(8);
	EXPECT_TRUE(start->right == NULL);
	DestroyTree(start);
}

TEST(UpdateWidth_AfterAddElem, RightInequality) {
	node_t* startnode;
	int n = 0, k = 0;
	startnode = Addnode(4, 10);
	startnode = Addnode(2, 3);
	startnode = Addnode(1, 50);
	n = startnode->width;
	startnode = Addnode(3, 1);
	k = startnode->width;
	EXPECT_TRUE(k > n);
	DestroyTree(startnode);
}

TEST(FindElem, Rightexpression) {
	node_t* start, *find;
	start = Addnode(4, 10);
	start = Addnode(2, 3);
	start = Addnode(1, 50);
	find = *Findnode(1);
	EXPECT_EQ(find,start->left->left);
	DestroyTree(start);
}
