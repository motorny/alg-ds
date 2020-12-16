#include "pch.h"
#include "..//LAB_E1/E1.c"



TEST(add, add_something) {
	node_t* tree = NULL;
	tree = add_node(tree, 1);
	tree = add_node(tree, 0);
	tree = add_node(tree, 3);

	ASSERT_TRUE(tree->data == 1);
	ASSERT_TRUE(tree->left->data == 0);
	ASSERT_TRUE(tree->right->data == 3);
	ASSERT_TRUE(tree->parent == NULL);
	ASSERT_TRUE(tree->left->parent == tree);
	ASSERT_TRUE(tree->right->parent == tree);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->right->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->right->right == NULL);

	delete_tree(tree);
}
TEST(delete, delete_something) {
	node_t* tree = NULL;
	tree = add_node(tree, 1);
	tree = delete_node(tree, 1);
	ASSERT_TRUE(tree == NULL);

	delete_tree(tree);
}
TEST(delete, delete_something_more_harder) {
	node_t* tree = NULL;
	tree = add_node(tree, 5);
	tree = add_node(tree, 4);
	tree = add_node(tree, 3);
	tree = delete_node(tree, 4);
	ASSERT_TRUE(tree->right == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->left->parent == tree);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->data == 5);
	ASSERT_TRUE(tree->left->data == 3);

	delete_tree(tree);
}
TEST(delete, delete_something_hard_like_prev) {
	node_t* tree = NULL;
	tree = add_node(tree, 5);
	tree = add_node(tree, 4);
	tree = add_node(tree, 3);
	tree = delete_node(tree, 3);
	ASSERT_TRUE(tree->right == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->left->parent == tree);
	ASSERT_TRUE(tree->left->left == NULL);
	ASSERT_TRUE(tree->left->right == NULL);
	ASSERT_TRUE(tree->data == 5);
	ASSERT_TRUE(tree->left->data == 4);

	delete_tree(tree);
}

TEST(delete, delete_hard) {
	node_t* tree = NULL;
	tree = add_node(tree, 3);
	tree = add_node(tree, 2);
	tree = add_node(tree, 4);
	tree = delete_node(tree, 3);
	ASSERT_TRUE(tree->data == 2);
	ASSERT_TRUE(tree->right->data == 4);
	ASSERT_TRUE(tree->left == NULL);
	ASSERT_TRUE(tree->right->parent == tree);
	ASSERT_TRUE(tree->parent == NULL);
	print_tree(tree, 0);
	delete_tree(tree);
}

TEST(find_node, find_elements) {
	node_t* tree = NULL;
	ASSERT_TRUE(find(tree, 3) == FAIL);
	tree = add_node(tree, 3);
	tree = add_node(tree, 2);
	tree = add_node(tree, 4);
	tree = add_node(tree, 5);
	tree = add_node(tree, 1);
	tree = add_node(tree, 0);
	ASSERT_TRUE(find(tree, 1) == SUCCESS);
	ASSERT_TRUE(find(tree, 2) == SUCCESS);
	ASSERT_TRUE(find(tree, 3) == SUCCESS);
	ASSERT_TRUE(find(tree, 4) == SUCCESS);
	ASSERT_TRUE(find(tree, 5) == SUCCESS);
	ASSERT_TRUE(find(tree, 0) == SUCCESS);
	tree = delete_node(tree, 3);
	tree = delete_node(tree, 2);
	tree = delete_node(tree, 4);
	ASSERT_TRUE(find(tree, 6) == FAIL);
	tree = delete_node(tree, 5);
	tree = delete_node(tree, 1);
	tree = delete_node(tree, 0);
	ASSERT_TRUE(find(tree, 1) == FAIL);
	ASSERT_TRUE(find(tree, 2) == FAIL);
	ASSERT_TRUE(find(tree, 3) == FAIL);
	ASSERT_TRUE(find(tree, 4) == FAIL);
	ASSERT_TRUE(find(tree, 5) == FAIL);
	ASSERT_TRUE(find(tree, 0) == FAIL);

	delete_tree(tree);
}

TEST(fill, fill_first_one) {
	node_t* tree = NULL;
	tree = add_node(tree, 1);
	tree = fill_tree(tree);
	ASSERT_TRUE(tree->data == 0);
	ASSERT_TRUE(tree->parent == NULL);
	ASSERT_TRUE(tree->left == NULL);
	ASSERT_TRUE(tree->right == NULL);

	delete_tree(tree);
}

TEST(fill, fill_NULL) {
	node_t* tree = NULL;
	tree = fill_tree(tree);
	ASSERT_TRUE(tree == NULL);

	delete_tree(tree);
}

TEST(fill, fill_anything) {
	node_t* tree = NULL;
	tree = add_node(tree, 3);
	tree = add_node(tree, 1);
	tree = add_node(tree, 2);
	tree = add_node(tree, 4);
	tree = add_node(tree, 5);
	tree = add_node(tree, 7);
	tree = add_node(tree, 6);
	tree = add_node(tree, 8);
	tree = fill_tree(tree);
	ASSERT_TRUE(tree->data == 2);
	ASSERT_TRUE(tree->left->data == 1);
	ASSERT_TRUE(tree->right->data == 3);
	ASSERT_TRUE(tree->right->right->data == 2);
	ASSERT_TRUE(tree->right->right->right->data == 0);
	ASSERT_TRUE(tree->right->right->right->right->data == 0);
	ASSERT_TRUE(tree->right->right->right->left->data == 0);

	delete_tree(tree);
}

TEST(fill, fill_right_trees) {
	node_t* tree = NULL;
	tree = add_node(tree, 0);
	tree = add_node(tree, 1);
	tree = add_node(tree, 2);
	tree = add_node(tree, 3);
	tree = add_node(tree, 4);
	tree = add_node(tree, 5);
	tree = fill_tree(tree);
	ASSERT_TRUE(tree->data == 5);
	ASSERT_TRUE(tree->right->data == 4);
	ASSERT_TRUE(tree->right->right->data == 3);
	ASSERT_TRUE(tree->right->right->right->data == 2);
	ASSERT_TRUE(tree->right->right->right->right->data == 1);
	ASSERT_TRUE(tree->right->right->right->right->right->data == 0);

	delete_tree(tree);
}

TEST(length, length_zero) {
	node_t* tree = NULL;
	int a = length(tree, 0);
	ASSERT_TRUE(a == 0);

	delete_tree(tree);
}

TEST(length, length_of_seven) {
	node_t* tree = NULL;
	tree = add_node(tree, 4);
	tree = add_node(tree, 2);
	tree = add_node(tree, 6);
	tree = add_node(tree, 1);
	tree = add_node(tree, 3);
	tree = add_node(tree, 5);
	tree = add_node(tree, 7);
	int a = length(tree, 0);
	ASSERT_TRUE(a == 3);

	delete_tree(tree);
}