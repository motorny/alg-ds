#include "pch.h"
extern "C"
{
#include "labF.h"
}

Node* Create1NodeTree() {
	Node* n1 = (Node*)malloc(sizeof(Node));
	n1->key = 2;
	n1->father = NULL;
	n1->numberOfNodes = 1;
	n1->right = NULL;
	n1->left = NULL;

	return n1;
}

Node* Create2NodeLeftTree() {
	Node* n1 = (Node*)malloc(sizeof(Node));
	Node* n2 = (Node*)malloc(sizeof(Node));

	n2->key = 1;
	n2->father = n1;
	n2->numberOfNodes = 1;
	n2->right = NULL;
	n2->left = NULL;

	n1->key = 2;
	n1->father = NULL;
	n1->numberOfNodes = 2;
	n1->right = NULL;
	n1->left = n2;

	return n1;
}

Node* Create2NodeRightTree() {
	Node* n1 = (Node*)malloc(sizeof(Node));
	Node* n2 = (Node*)malloc(sizeof(Node));

	n2->key = 3;
	n2->father = n1;
	n2->numberOfNodes = 1;
	n2->right = NULL;
	n2->left = NULL;

	n1->key = 2;
	n1->father = NULL;
	n1->numberOfNodes = 2;
	n1->left = NULL;
	n1->right = n2;

	return n1;
}

Node* Create3NodeTree() {
	Node* n1 = (Node*)malloc(sizeof(Node));
	Node* n2 = (Node*)malloc(sizeof(Node));
	Node* n3 = (Node*)malloc(sizeof(Node));

	n3->key = 1;
	n3->father = n1;
	n3->numberOfNodes = 1;
	n3->right = NULL;
	n3->left = NULL;

	n2->key = 3;
	n2->father = n1;
	n2->numberOfNodes = 1;
	n2->right = NULL;
	n2->left = NULL;

	n1->key = 2;
	n1->father = NULL;
	n1->numberOfNodes = 3;
	n1->left = n3;
	n1->right = n2;

	return n1;
}

TEST(AtT_AddToEmptyTree_notCrush) {
	Node* tree = NULL;
	int res = AtT(&tree, tree, 2);

	ASSERT_EQ(res == TRUE, 1);
	ASSERT_EQ(tree->key == 2, 1);
	ASSERT_EQ(tree->left == NULL, 1);
	ASSERT_EQ(tree->right == NULL, 1);
	ASSERT_EQ(tree->father == NULL, 1);
	ASSERT_EQ(tree->numberOfNodes == 1, 1);
}

TEST(AtT_AddNotToEmptyTree_notCrush) {
	Node* tree = Create1NodeTree();
	// äîáàâëÿåì óæå ñóùåñòâóþùèé è ïðîâåðèì ÷òî res=false;
	int res = AtT(&tree, tree, 2);
	ASSERT_EQ(res == FALSE, 1);

	// äîáàâëÿåì ñïðàâà
	res = AtT(&tree, tree, 3);
	ASSERT_EQ(res == TRUE, 1);
	ASSERT_EQ(tree->right->key == 3, 1);
	ASSERT_EQ(tree->right->left == NULL, 1);
	ASSERT_EQ(tree->right->right == NULL, 1);
	ASSERT_EQ(tree->right->father == tree, 1);
	ASSERT_EQ(tree->right->numberOfNodes == 1, 1);

	ASSERT_EQ(tree->key == 2, 1);
	ASSERT_EQ(tree->left == NULL, 1);
	ASSERT_EQ(tree->right == NULL, 0);
	ASSERT_EQ(tree->father == NULL, 1);
	ASSERT_EQ(tree->numberOfNodes == 2, 1);

	// äîáàâëÿåì ñëåâà
	res = AtT(&tree, tree, 1);
	ASSERT_EQ(res == TRUE, 1);
	ASSERT_EQ(tree->left->key == 1, 1);
	ASSERT_EQ(tree->left->left == NULL, 1);
	ASSERT_EQ(tree->left->right == NULL, 1);
	ASSERT_EQ(tree->left->father == tree, 1);
	ASSERT_EQ(tree->left->numberOfNodes == 1, 1);

	ASSERT_EQ(tree->key == 2, 1);
	ASSERT_EQ(tree->left == NULL, 0);
	ASSERT_EQ(tree->right == NULL, 0);
	ASSERT_EQ(tree->father == NULL, 1);
	ASSERT_EQ(tree->numberOfNodes == 3, 1);
}



TEST(FKLT_emptyTree_notCrush) {
	Node* tree = NULL, * currentNode;

	currentNode = FKLT(tree, 1, 1);
	ASSERT_EQ(currentNode == NULL, 1);
}

TEST(FKLT_1NodeTree_notCrush) {
	Node* tree = Create1NodeTree(), * currentNode;

	// check for each node each 'k'
	currentNode = FKLT(tree, 1, -1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, -1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 3, -1);
	ASSERT_EQ(currentNode == NULL, 1);

	currentNode = FKLT(tree, 1, 0);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, 0);
	ASSERT_EQ(currentNode == tree, 1);
	currentNode = FKLT(tree, 3, 0);
	ASSERT_EQ(currentNode == NULL, 1);

	currentNode = FKLT(tree, 1, 1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, 1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 3, 1);
	ASSERT_EQ(currentNode == NULL, 1);
}

TEST(FKLT_2NodeLeft_notCrush) {
	Node* tree = Create2NodeLeftTree(), * currentNode;

	currentNode = FKLT(tree, 1, -1);
	ASSERT_EQ(currentNode == tree, 1);
	currentNode = FKLT(tree, 2, -1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 3, -1);
	ASSERT_EQ(currentNode == NULL, 1);

	currentNode = FKLT(tree, 1, 0);
	ASSERT_EQ(currentNode == tree->left, 1);
	currentNode = FKLT(tree, 2, 0);
	ASSERT_EQ(currentNode == tree, 1);
	currentNode = FKLT(tree, 3, 0);
	ASSERT_EQ(currentNode == NULL, 1);

	currentNode = FKLT(tree, 1, 1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, 1);
	ASSERT_EQ(currentNode == tree->left, 1);
	currentNode = FKLT(tree, 3, 1);
	ASSERT_EQ(currentNode == NULL, 1);
}

TEST(FKLT_2NodeRight_notCrush) {
	Node* tree = Create2NodeRightTree(), * currentNode;

	currentNode = FKLT(tree, 1, -1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, -1);
	ASSERT_EQ(currentNode == tree->right, 1);
	currentNode = FKLT(tree, 3, -1);
	ASSERT_EQ(currentNode == NULL, 1);

	currentNode = FKLT(tree, 1, 0);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, 0);
	ASSERT_EQ(currentNode == tree, 1);
	currentNode = FKLT(tree, 3, 0);
	ASSERT_EQ(currentNode == tree->right, 1);

	currentNode = FKLT(tree, 1, 1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, 1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 3, 1);
	ASSERT_EQ(currentNode == tree, 1);
}

TEST(FKLT_3Node_notCrush) {
	int k = 1;
	Node* tree = Create3NodeTree(), * currentNode;

	currentNode = FKLT(tree, 1, -1);
	ASSERT_EQ(currentNode == tree, 1);
	currentNode = FKLT(tree, 2, -1);
	ASSERT_EQ(currentNode == tree->right, 1);
	currentNode = FKLT(tree, 3, -1);
	ASSERT_EQ(currentNode == NULL, 1);

	currentNode = FKLT(tree, 1, 0);
	ASSERT_EQ(currentNode == tree->left, 1);
	currentNode = FKLT(tree, 2, 0);
	ASSERT_EQ(currentNode == tree, 1);
	currentNode = FKLT(tree, 3, 0);
	ASSERT_EQ(currentNode == tree->right, 1);

	currentNode = FKLT(tree, 1, 1);
	ASSERT_EQ(currentNode == NULL, 1);
	currentNode = FKLT(tree, 2, 1);
	ASSERT_EQ(currentNode == tree->left, 1);
	currentNode = FKLT(tree, 3, 1);
	ASSERT_EQ(currentNode == tree, 1);
}

TEST(ClearTree_AllVariants_notCrush) {
	Node* tree = NULL;
	ClearTree(&tree);
	ASSERT_EQ(tree == NULL, 1);
	tree = Create1NodeTree();
	ClearTree(&tree);
	ASSERT_EQ(tree == NULL, 1);
	tree = Create2NodeLeftTree();
	ClearTree(&tree);
	ASSERT_EQ(tree == NULL, 1);
	tree = Create2NodeRightTree();
	ClearTree(&tree);
	ASSERT_EQ(tree == NULL, 1);
	tree = Create3NodeTree();
	ClearTree(&tree);
	ASSERT_EQ(tree == NULL, 1);
}
