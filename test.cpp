#include "pch.h"
//#include "vld.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef struct Node {
	struct Node* parent;
	struct Node* right;
	struct Node* left;
	int data;
}Node_t;
Node_t* add(Node_t* root, int newData) {
	if (!root) {
		root = (Node_t*)malloc(sizeof(Node_t));
		if (!root)return ERROR;
		root->parent = NULL;
		root->data = newData;
		root->right = NULL;
		root->left = NULL;
	}
	else {
		Node_t* node = root;
		while (node)
		{
			if (node->data == newData)
				break;
			if (node->data > newData) {
				if (node->left)
					node = node->left;
				else {
					node->left = (Node_t*)malloc(sizeof(Node_t));
					node->left->parent = node;
					node->left->data = newData;
					node->left->left = NULL;
					node->left->right = NULL;
					break;
				}
			}
			else {
				if (node->right)
					node = node->right;
				else {
					node->right = (Node_t*)malloc(sizeof(Node_t));
					if (node->right)
						node->right->parent = node;
					else
						return ERROR;
					node->right->data = newData;
					node->right->left = NULL;
					node->right->right = NULL;
					break;
				}
			}
		}
	}
	return root;
}
int max(Node_t* root) {
	while (root->right)
	{
		root = root->right;
	}
	return root->data;
}
int length(Node_t* root, int len) {
	if (root) {
		int a = length(root->left, len + 1);
		int b = length(root->right, len + 1);
		return  (a > b) ? a : b;

	}
	else
		return len;
}
Node_t* fillTree(Node_t* root) {
	if (root) {
		int a = length(root->left, 0);
		int b = length(root->right, 0);
		root->data = (a > b) ? a - b : b - a;
		fillTree(root->left);
		fillTree(root->right);
		return root;
	}
	return NULL;
}
Node_t* remove(Node_t* root, int newData) {
	if (root)
		if (root->data == newData) {
			if (root->parent) {
				if (!root->left && !root->right) {
					if (root->parent->left == root)
						root->parent->left = NULL;
					else
						root->parent->right = NULL;
					free(root);
					root = NULL;
				}
				else if (root->left && !root->right) {
					if (root->parent->left == root) {
						root->parent->left = root->left;
						root->left->parent = root->parent;
					}
					else {
						root->parent->right = root->left;
						root->left->parent = root->parent;
					}
					free(root);
					root = NULL;
				}
				else if (!root->left && root->right) {
					if (root->parent->right == root) {
						root->parent->right = root->right;
						root->right->parent = root->parent;
					}
					else {
						root->parent->left = root->right;
						root->right->parent = root->parent;
					}
					free(root);
					root = NULL;
				}
				else {
					int m = max(root->left);
					root->data = m;
					remove(root->left, m);
				}
			}
			else {
				if (!root->left && !root->right) {
					free(root);
					root = NULL;

				}
				else if (root->left && !root->right) {
					Node_t* tmp = root->left;
					free(root);
					tmp->parent = NULL;
					root = tmp;
				}
				else if (!root->left && root->right) {
					Node_t* tmp = root->right;
					free(root);
					tmp->parent = NULL;
					root = tmp;
				}
				else {
					int m = max(root->left);
					root->data = m;
					remove(root->left, m);
				}
			}
		}
		else if (newData > root->data) {
			remove(root->right, newData);
		}
		else {
			remove(root->left, newData);
		}
	return root;
}
int find(Node_t* root, int newData) {
	if (root) {
		if (root->data == newData)
			return TRUE;
		else if (newData < root->data)
			return find(root->left, newData);
		else
			return  find(root->right, newData);
	}
	else
		return FALSE;
}
void freeTree(Node_t* root) {
	if (root) {
		//	printf("%i ", (root->data));

		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}
void printTree(Node_t* tree, int index)
{
	if (tree)
	{
		printf("%d %d\n", index, tree->data);
		printTree(tree->left, index + 1);
		printTree(tree->right, index + 1);
	}
}
int main(int argc, char* argv[]) {

/*	Node_t* root = NULL;
	char c, operation, number[255];
	int index = 0, data;

	c = getchar();
	while (c != EOF)
	{
		operation = c;
		c = getchar();
		while (isspace(c))
		{
			c = getchar();
		}
		while (isdigit(c))
		{
			number[index++] = c;
			c = getchar();
		}
		number[index] = '\0';
		data = atoi(number);
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			root = add(root, data);
			break;
		}
		case 'r':
		{
			root = remove(root, data);
			break;
		}
		case 'f':
		{
			if (find(root, data))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
			break;
		}
		default: {
			freeTree(root);
			return 0;
		}

		}
		if (c == '\n')
		{
			c = getchar();
		}

	}
	freeTree(root);	*/
	testing::InitGoogleTest(&argc, argv);
	return  RUN_ALL_TESTS();;
}


TEST(tree,addSomeValuesReturnCorrectTree) {
	Node_t* root = NULL;
	root = add(root, 1);
	root = add(root, 0);
	root = add(root, 3);
	 
	ASSERT_TRUE(root->data==1);
	ASSERT_TRUE(root->left->data== 0);
	ASSERT_TRUE(root->right->data== 3);
	ASSERT_TRUE(root->parent== NULL);
	ASSERT_TRUE(root->left->parent== root);
	ASSERT_TRUE(root->right->parent== root);
	ASSERT_TRUE(root->left->left== NULL);
	ASSERT_TRUE(root->right->left== NULL);
	ASSERT_TRUE(root->left->right== NULL);
	ASSERT_TRUE(root->right->right== NULL);
	freeTree(root);
}
TEST(tree, removeSimpleRootValueReturnNULL) {
	Node_t* root = NULL;
	root = add(root, 1);
	root = remove(root, 1);
	ASSERT_TRUE(root == NULL);

	freeTree(root);
}
TEST(tree, removeSimpleLeftValueReturnCorrectTree) {
	Node_t* root = NULL;
	root = add(root, 5);
	root = add(root, 4);
	root = add(root, 3);
	root = remove(root, 4);
	ASSERT_TRUE(root->right == NULL);
	ASSERT_TRUE(root->left->right == NULL);
	ASSERT_TRUE(root->left->parent == root);
	ASSERT_TRUE(root->left->left == NULL);
	ASSERT_TRUE(root->left->right == NULL);
	ASSERT_TRUE(root->data == 5);
	ASSERT_TRUE(root->left->data == 3);

	freeTree(root);
}
TEST(tree, removeSimpleLeafLeftRootValueReturnCorrectTree) {
	Node_t* root = NULL;
	root = add(root, 5);
	root = add(root, 4);
	root = add(root, 3);
	root = remove(root, 3);
	ASSERT_TRUE(root->right == NULL);
	ASSERT_TRUE(root->left->right == NULL);
	ASSERT_TRUE(root->left->parent == root);
	ASSERT_TRUE(root->left->left == NULL);
	ASSERT_TRUE(root->left->right == NULL);
	ASSERT_TRUE(root->data == 5);
	ASSERT_TRUE(root->left->data == 4);

	freeTree(root);
}
TEST(tree, removeComplexRootValueReturnCorrectTree) {
	Node_t* root = NULL;
	root = add(root, 3);
	root = add(root, 2);
	root = add(root, 4);
	root = remove(root, 3);
	ASSERT_TRUE(root->data == 2);
	ASSERT_TRUE(root->right->data == 4);
	ASSERT_TRUE(root->left == NULL);
	ASSERT_TRUE(root->right->parent == root);
	ASSERT_TRUE(root->parent == NULL);
	printTree(root,0);
	freeTree(root);
}
	TEST(tree, removeRightLeafValueReturnCorrectTree) {
		Node_t* root = NULL;
		root = add(root, 1);
		root = add(root, 2);
		root = remove(root, 2);
		ASSERT_TRUE(root->data == 1);
		ASSERT_TRUE(root->parent == NULL);
		ASSERT_TRUE(root->left == NULL);
		ASSERT_TRUE(root->right == NULL);
		freeTree(root);
}
	TEST(tree, findSomeValuesReturnCorrectValues) {
		Node_t* root = NULL;
		ASSERT_TRUE(find(root, 3) == FALSE);
		root = add(root, 3);
		root = add(root, 2);
		root = add(root, 4);
		root = add(root, 5);
		root = add(root, 1);
		root = add(root, 0);
		ASSERT_TRUE(find(root,1)==TRUE);
		ASSERT_TRUE(find(root,2)==TRUE);
		ASSERT_TRUE(find(root, 3) == TRUE);
		ASSERT_TRUE(find(root, 4) == TRUE);
		ASSERT_TRUE(find(root, 5) == TRUE);
		ASSERT_TRUE(find(root, 0) == TRUE);
		root = remove(root, 3);
		root = remove(root, 2);
		root = remove(root, 4);
		ASSERT_TRUE(find(root, 6) == FALSE);
		root = remove(root, 5);
		root = remove(root, 1);
		root = remove(root, 0);
		ASSERT_TRUE(find(root, 1) == FALSE);
		ASSERT_TRUE(find(root, 2) == FALSE);
		ASSERT_TRUE(find(root, 3) == FALSE);
		ASSERT_TRUE(find(root, 4) == FALSE);
		ASSERT_TRUE(find(root, 5) == FALSE);
		ASSERT_TRUE(find(root, 0) == FALSE);
		freeTree(root);
	}
	TEST(labE_1,fillTreeOneValueReturnZero) {
		Node_t* root = NULL;
		root = add(root,1);
		root = fillTree(root);
		ASSERT_TRUE(root->data == 0);
		ASSERT_TRUE(root->parent == NULL);
		ASSERT_TRUE(root->left == NULL);
		ASSERT_TRUE(root->right == NULL);
		freeTree(root);
   }
	TEST(labE_1, fillEmptyTreeReturnNULL) {
		Node_t* root = NULL;
		root = fillTree(root);
		ASSERT_TRUE(root==NULL);
		freeTree(root);
	}
	TEST(labE_1, fillSomeValuesTreeRecurnCorrectAnswer) {
		Node_t* root = NULL;
		root = add(root, 3);
		root = add(root, 1);
		root = add(root, 2);
		root = add(root, 4);
		root = add(root, 5);
		root = add(root, 7);
		root = add(root, 6);
		root = add(root, 8);
		root = fillTree(root);
		ASSERT_TRUE(root->data ==2);
		ASSERT_TRUE(root->left->data == 1);
		ASSERT_TRUE(root->right->data == 3);
		ASSERT_TRUE(root->right->right->data == 2);
		ASSERT_TRUE(root->right->right->right->data == 0);
		ASSERT_TRUE(root->right->right->right->right->data == 0);
		ASSERT_TRUE(root->right->right->right->left->data == 0);

		freeTree(root);
	}
	TEST(labE_1, FillTreeThatHasOnlyRightNodesReturnCorrectTree) {
		Node_t* root = NULL;
		root=  add(root, 0);
		root = add(root, 1);
		root = add(root, 2);
		root = add(root, 3);
		root = add(root, 4);
		root = add(root, 5);
		root = fillTree(root);
		ASSERT_TRUE(root->data == 5);
		ASSERT_TRUE(root->right->data == 4);
		ASSERT_TRUE(root->right->right->data == 3);
		ASSERT_TRUE(root->right->right->right->data == 2);
		ASSERT_TRUE(root->right->right->right->right->data == 1);
		ASSERT_TRUE(root->right->right->right->right->right->data == 0);
		freeTree(root);
	}
	TEST(labE_1, lengthEmptyTreeReturnNULL) {
		Node_t* root = NULL;
		int a = length(root,0);
		ASSERT_TRUE(a == 0);
		freeTree(root);
	}
	TEST(labE_1, lengthBalancedSevenValuesTreeReturnThree) {
		Node_t* root = NULL;
		root = add(root, 4);
		root = add(root, 2);
		root = add(root, 6);
		root = add(root, 1);
		root = add(root, 3);
		root = add(root, 5);
		root = add(root, 7);
		int a = length(root, 0);
		ASSERT_TRUE(a == 3);
		freeTree(root);
	}