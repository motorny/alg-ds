#include "pch.h"

extern "C" {
#include "..//splay/Header.h"
}


TEST(Add_TwoElems, RightPlace) {
	node_t* startnode = NULL;
	Add(&startnode, 2);
	Add(&startnode, 8);
	EXPECT_TRUE(startnode->left == NULL);
	EXPECT_TRUE(startnode->right->key == 8);
	EXPECT_TRUE(startnode->key == 2);
}

TEST(FindElem, Rightexpression) {
	node_t* start = NULL, * find;
	Add(&start, 10);
	Add(&start, 3);
	Add(&start, 11);
	find = Findnode(start, 3);
	EXPECT_EQ(find, start->left);
}


TEST(DeleteElem, Rightexpression) {
	node_t* start = NULL, * find;
	Add(&start, 10);
	Add(&start, 3);
	Add(&start, 11);
	Delete(&start, Findnode(start, 3));
	find = Findnode(start, 3);
	EXPECT_TRUE(find == NULL);
	EXPECT_TRUE(start->left == NULL);
}

TEST(Splay, Rightexpression) {
	node_t* start = NULL, * find;
	Add(&start, 10);
	Add(&start, 3);
	Add(&start, 11);
	start = splay(Findnode(start, 3));
	EXPECT_TRUE(start->key == 3);
}