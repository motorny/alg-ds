#include "pch.h"
#include "../RedBlack_Tree/rbtree.c"

TEST(Insert, InputNullPtr) {
	Node* tree = NULL;
	EXPECT_EQ(NULL, insert(1, &tree));
}

TEST(Insert, AddElements) {
	Node* tree = NIL;
	insert(3, &tree);
	insert(2, &tree);
	insert(5, &tree);
	EXPECT_EQ(3, tree->data);
	EXPECT_EQ(2, tree->left->data);
	EXPECT_EQ(5, tree->right->data);
	EXPECT_EQ(NIL, tree->right->left);
	EXPECT_EQ(NIL, tree->right->right);
}

TEST(Insert, CheckColorRoots) {
	Node* tree = NIL;
	insert(3, &tree);
	insert(2, &tree);
	insert(5, &tree);
	insert(1, &tree);

	EXPECT_EQ(BLACK, tree->color);
	EXPECT_EQ(BLACK, tree->left->color);
	EXPECT_EQ(RED, tree->left->left->color);
}

Node* CreateTree(T value) {
	Node* tree = (Node*)malloc(sizeof(Node));
	tree->data = value;
	tree->right = NIL;
	tree->left = NIL;
	tree->color = RED;
	return tree;
}

TEST(Find, FindExistRoot) {
	Node* tree = CreateTree(3);
	tree->left = CreateTree(1);

	EXPECT_EQ(tree, findNode(3, tree));
	EXPECT_EQ(tree->left, findNode(1, tree));
	free(tree->left);
	free(tree);
}

TEST(Find, FindNotExistRoot) {
	Node* tree = CreateTree(3);
	tree->left = CreateTree(1);

	EXPECT_EQ(NULL, findNode(4, tree));
	free(tree->left);
	free(tree);
}

TEST(Delete, DeleteExistElement) {
	Node* tree = CreateTree(3);
	tree->left = CreateTree(1);
	tree->left->parent = tree;

	deleteD(1, &tree);
	EXPECT_EQ(NIL, tree->left);
	free(tree->left);
	free(tree);
}

TEST(Delete, DeleteNotExistElement) {
	Node* tree = CreateTree(3);
	tree->left = CreateTree(1);
	tree->right = CreateTree(5);
	tree->left->parent = tree;
	tree->right->parent = tree;

	deleteD(2, &tree);
	EXPECT_EQ(3, tree->data);
	EXPECT_EQ(1, tree->left->data);
	EXPECT_EQ(5, tree->right->data);
	free(tree->left);
	free(tree->right);
	free(tree);
}