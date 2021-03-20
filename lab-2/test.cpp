#include "pch.h"


TEST(Btree, ins_returnInsertIt) {

	int key = 1;
	node* newnode;
	node root;
	int upKey;
	KeyStatus value;
	value = ins(root, key, &upKey, &newnode);
	EXPECT_EQ(value, InsertIt);
}

TEST(Btree, searchPos_return0) {
	int pos, i, n, key=1;
	node ptr;
	n = ptr->n;
	pos = searchPos(key, ptr.keys, n);
	EXPECT_EQ(pos, 0);
	
}

TEST(Btree, del_returnSearchFailure) {
	node root;
	node* uproot;
	KeyStatus value;
	value = del(root, key);
	EXPECT_EQ(value, SearchFailure);
}