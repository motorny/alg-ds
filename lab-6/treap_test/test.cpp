

#include "pch.h"
extern "C" {
#include "treap.h"
}
//		12
//	6		9
//	  2

node* build_simple_tree() {
	node* p1 = init_node(12);
	node* p2 = init_node(6);
	node* p3 = init_node(2);
	node* p4 = init_node(9);
	p1->prior = p1->val;
	p2->prior = p2->val;
	p3->prior = p3->val;
	p4->prior = p4->val;
	p1->left = p2;
	p1->right = p4;
	p2->right = p3;
	p2->left = NULL;
	p3->left = p3->right = p4->right = p4->left = NULL;
	p1->count = 4;
	p2->count = 2;
	p4->count = p3->count = 1;
	return p1;
}



TEST(TestGetCount, EmptyNodeReturnZero) {
	node* p = NULL;
	EXPECT_EQ(get_count(p), 0);
}

TEST(TestGetCount, NonEmptyNodeReturnValidVal) {
	node* p = init_node(3);
	p->count = 2;
	EXPECT_EQ(get_count(p), 2);
	free_tree(p);
}

TEST(TestUpdateCount, NonEmptyNodeTwoSiblingsReturnValidVal) {
	node* root = build_simple_tree();
	root->count = 0;
	int correct_count = root->left->count + root->right->count + 1;
	update_count(root);
	int cur_count = root->count;
	EXPECT_EQ(cur_count, correct_count);
	free_tree(root);
}

TEST(TestUpdateCount, NonEmptyNodeOneSiblingsReturnValidVal) {
	node* p = build_simple_tree()->left;
	p->count = 0;
	int correct_count = p->right->count + 1;
	update_count(p);
	int cur_count = p->count;
	EXPECT_EQ(cur_count, correct_count);
	free_tree(p);
}

TEST(TestUpdateCount, NonEmptyNodeNoSiblingsReturnValidVal) {
	node* p = build_simple_tree()->right;
	p->count = 0;
	int correct_count =  1;
	update_count(p);
	int cur_count = p->count;
	EXPECT_EQ(cur_count, correct_count);
	free_tree(p);
}




TEST(TestMerge, TwoEmptyTreapsReturnEmpty) {
	node* l, *r;
	l = r = NULL;
	node* res = merge(l, r);
	EXPECT_TRUE(!res);
	free_tree(res);
	free_tree(r);
	free_tree(l);
}

TEST(TestMerge, OneEmptyTreapsReturnSecondTreap) {
	node* l, * r;
	l  = NULL;
	r = build_simple_tree();
	node* res = merge(l, r);
	EXPECT_EQ(res, r);
	free_tree(res);

}

TEST(TestMerge, NonEmptyTreapsReturnValidVal) {
	node* l, * r;
	l = init_node(33);
	r = build_simple_tree();
	node* res = merge(l, r);
	EXPECT_TRUE(res!=r);
	EXPECT_TRUE(res == l);
	EXPECT_TRUE(res != NULL);
	EXPECT_EQ(res->count, l->count);
	free_tree(res);

}


TEST(TestSplit, EmptyTreapReturnBothEmpty) {
	node* root = NULL;
	node* l, * r;
	split(1, root, &l, &r, DEFAULT_ADD_VAL);
	EXPECT_TRUE(!l);
	EXPECT_TRUE(!r);
	free_tree(root);

}

TEST(TestSplit, KeyLessThanOneReturnEmptyAndInitialTreap) {
	node* root = build_simple_tree();
	node* l, * r;
	split(0, root, &l, &r, DEFAULT_ADD_VAL);
	EXPECT_TRUE(!l);
	EXPECT_TRUE(r == root);
	free_tree(root);

}

TEST(TestSplit, KeyNonZeroReturnValidVal) {
	node* root = build_simple_tree();
	node* l, * r;
	int root_size = root->count;
	split(1, root, &l, &r, DEFAULT_ADD_VAL);
	EXPECT_TRUE(l);
	EXPECT_TRUE(r);
	EXPECT_EQ(r->count, root_size-1);
	EXPECT_EQ(l->count, 1);
	free_tree(r);
	free_tree(l);
}


TEST(TestSplit, KeyMoreThanSizeReturnInitialTreapAndEmpty) {
	node* root = build_simple_tree();
	node* l, * r;
	int root_size = root->count;
	split(root_size + 1, root, &l, &r, DEFAULT_ADD_VAL);
	EXPECT_TRUE(!r);
	EXPECT_TRUE(l == root);
	free_tree(l);

}

TEST(TestInsert, EmptyTreapNodeBecomesRoot) {
	node* root = NULL;
	int old_root_size = 0;
	insert(33, 0, &root);
	EXPECT_TRUE(root);
	EXPECT_TRUE(root->count - old_root_size == 1);
	EXPECT_EQ(33, root->val);
	free_tree(root);
}

TEST(TestInsert, NegativePosDoNothing) {
	node* root = build_simple_tree();
	int old_root_size = 4;
	insert(33, -3, &root);
	EXPECT_TRUE(root->count == old_root_size);
	free_tree(root);
}

TEST(TestDelete, NegativeIndexDoNothing) {
	node* root = build_simple_tree();
	int old_root_size = 4;
	int res = del(-1, &root);
	EXPECT_EQ(old_root_size, root->count);
	EXPECT_EQ(res, NOTHING_DELETED);

	free_tree(root);
}


TEST(TestDelete, OutOfRangeIndexDoNothing) {
	node* root = build_simple_tree();
	int old_root_size = 4;
	int res = del(old_root_size, &root);
	EXPECT_EQ(old_root_size, root->count);
	EXPECT_EQ(res, NOTHING_DELETED);

	free_tree(root);
}
TEST(TestDelete, DeleteElemReturnValidVal) {
	node* root = build_simple_tree();
	int old_root_size = 4;
	int res = del(0, &root);
	EXPECT_EQ(old_root_size, root->count + 1);
	EXPECT_EQ(res, SOMETHING_DELETED);
	free_tree(root);
}



