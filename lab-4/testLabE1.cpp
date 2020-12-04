#include "pch.h"
//#include "..\SearchTree\LabE1_Site.c"


//TEST(add, addingToEmptyTree)
//{
//	TREE* tree = NULL;
//	addToTree(&tree, 10);
//	ASSERT_EQ(10, tree->data);
//	ASSERT_EQ(NULL, tree->left);
//	ASSERT_EQ(NULL, tree->right);
//	destroyTree(tree);
//}
//
//TEST(add, addingToLeftNode)
//{
//	TREE* tree = NULL;
//	addToTree(&tree, 5);
//	addToTree(&tree, 4);
//	ASSERT_EQ(5, tree->data);
//	ASSERT_EQ(4, tree->left->data);
//	ASSERT_EQ(NULL, tree->right);
//	destroyTree(tree);
//}
//
//TEST(add, addingToRightNode)
//{
//	TREE* tree = NULL;
//	addToTree(&tree, 5);
//	addToTree(&tree, 6);
//	ASSERT_EQ(5, tree->data);
//	ASSERT_EQ(6, tree->right->data);
//	ASSERT_EQ(NULL, tree->left);
//	destroyTree(tree);
//}
//
//TREE* createTree()
//{
//	TREE* tree = NULL;
//	addToTree(&tree, 5);
//	addToTree(&tree, 6);
//	addToTree(&tree, 4);
//	addToTree(&tree, 2);
//	addToTree(&tree, 1);
//	addToTree(&tree, 10);
//
//	return tree;
//}
//
//TEST(find, elemIsInTheTree)
//{
//	TREE* tree = createTree();
//	ASSERT_EQ(1, findByValue(tree, 4));
//	ASSERT_EQ(1, findByValue(tree, 10));
//	destroyTree(tree);
//}
//
//TEST(find, elemIsNotInTheTree)
//{
//	TREE* tree = createTree();
//	ASSERT_EQ(0, findByValue(tree, 9));
//	ASSERT_EQ(0, findByValue(tree, 11));
//	destroyTree(tree);
//}
//
//TEST(del, delElemIsInTheTree)
//{
//	TREE* tree = createTree();
//	delByData(&tree, 4);
//	ASSERT_EQ(0, findByValue(tree, 4));
//	destroyTree(tree);
//}
//
//TEST(height, subTreeHeihtDif)
//{
//	TREE* tree = createTree();
//	tree = subtreeHeightDif(tree);
//	ASSERT_EQ(tree->data, 1);
//	ASSERT_EQ(tree->left->data, 3);
//	ASSERT_EQ(tree->right->data, 2);
//	ASSERT_EQ(tree->left->left->data, 2);
//	destroyTree(tree);
//}