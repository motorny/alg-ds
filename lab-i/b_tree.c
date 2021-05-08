



#include "b_tree.h"



void InitBtree(Btree_t* tree) {
	tree->root = NULL;
}

static int SplitChildrenBtree(Btree_node_t* node, int index) {
	if (index > 2 * FACTOR - 1)
		return IND_ERR;
	else if (node == NULL)
		return MY_FAIL;
	else {
		Btree_node_t* newNode = (Btree_node_t*)malloc(sizeof(Btree_node_t));
		Btree_node_t* childNode = node->children[index];

		if (newNode == NULL)
			return MEM_ERR;

		newNode->ifLeaf = childNode->ifLeaf;
		newNode->numKeys = FACTOR - 1;
		memcpy(&newNode->key[0], &childNode->key[FACTOR], (FACTOR - 1) * sizeof(int));

		if (childNode->ifLeaf == FALSE)
			memcpy(&newNode->children[0], &childNode->children[FACTOR], (FACTOR) * sizeof(Btree_node_t*));
		childNode->numKeys = FACTOR - 1;

		if (node->numKeys > index)
			memmove(&node->children[index + 2], &node->children[index + 1], (node->numKeys - index) * sizeof(Btree_node_t*));
		node->children[index + 1] = newNode;

		if (node->numKeys > index)
			memmove(&node->key[index + 1], &node->key[index], (node->numKeys - index) * sizeof(int));
		node->key[index] = childNode->key[FACTOR - 1];
		node->numKeys++;

		return SUCCESS;
	}
}

static int SearchBin(int arr[], int length, int key) {
	int first = 0;
	int last = length;

	if (length == 0)
		return 0;
	if (key < arr[first])
		return 0;
	if (key > arr[last - 1])
		return last;

	while (first < last)
		if (key <= arr[first + (last - first) / 2])
			last = first + (last - first) / 2;
		else
			first = first + (last - first) / 2 + 1;

	return last;
}

int AddToBtree(Btree_t* tree, int key) {
	int index = 0;
	Btree_node_t* node;

	if (tree == NULL)
		return MY_FAIL;

	if (tree->root == NULL) {
		Btree_node_t* newRoot = (Btree_node_t*)malloc(sizeof(Btree_node_t));

		if (newRoot == NULL)
			return MEM_ERR;

		newRoot->numKeys = 0;
		newRoot->ifLeaf = TRUE;

		tree->root = newRoot;
	}
	else if (tree->root->numKeys == 2 * FACTOR - 1) {
		Btree_node_t* newRoot = (Btree_node_t*)malloc(sizeof(Btree_node_t));

		if (newRoot == NULL)
			return MEM_ERR;

		newRoot->children[0] = tree->root;
		newRoot->ifLeaf = FALSE;
		newRoot->numKeys = 0;

		tree->root = newRoot;
	}
	else if (tree->root->numKeys > 0) {
		index = SearchBin(tree->root->key, tree->root->numKeys, key);
		if (index < tree->root->numKeys && tree->root->key[index] == key)
			return SUCCESS;
	}

	node = tree->root;
	while (node->ifLeaf == FALSE) {
		if (node->children[index]->numKeys == 2 * FACTOR - 1) {
			if (SplitChildrenBtree(node, index) != SUCCESS)
				return MY_FAIL;

			if (key > node->key[index])
				index++;
		}
		if (index < node->numKeys && node->key[index] == key)
			return SUCCESS;
		node = node->children[index];
		index = SearchBin(node->key, node->numKeys, key);
		if (index < node->numKeys && node->key[index] == key)
			return SUCCESS;
	}

	if (node->numKeys > index)
		memmove(&node->key[index + 1], &node->key[index], (node->numKeys - index) * sizeof(int));
	node->key[index] = key;
	node->numKeys++;

	return SUCCESS;
}

Btree_node_t* FindInBtree(Btree_t* tree, int key) {
	int index = 0;
	Btree_node_t* node;

	if (tree == NULL)
		return NULL;

	node = tree->root;
	if (node == NULL)
		return NULL;

	while (node->ifLeaf == FALSE) {
		index = SearchBin(node->key, node->numKeys, key);

		if (index < node->numKeys && node->key[index] == key)
			return node;

		node = node->children[index];
	}
	index = SearchBin(node->key, node->numKeys, key);

	if (index < node->numKeys && node->key[index] == key)
		return node;
	else
		return NULL;
}

static void FreeNodeBtree(Btree_node_t* node) {
	int counter;

	if (node->ifLeaf == FALSE) {
		for (counter = 0; counter <= node->numKeys; counter++) {
			FreeNodeBtree(node->children[counter]);
			free(node->children[counter]);
		}
	}
	else
		return;
}

void DestroyBtree(Btree_t* tree) {
	if (tree->root != NULL) {
		FreeNodeBtree(tree->root);
		free(tree->root);
		tree->root = NULL;
	}
}

static void PrintNodeBtree(Btree_node_t* node, int level) {
	int i;

	if (node != NULL && level >= 0) {
		for (i = 0; i < level; i++)
			printf("    ");
		for (i = 0; i < node->numKeys; i++) {
			printf("%i", node->key[i]);
			if (i != node->numKeys - 1)
				printf(", ");
		}
		printf("\n");
		if (node->ifLeaf == TRUE)
			return;
		for (i = 0; i <= node->numKeys; i++)
			PrintNodeBtree(node->children[i], level + 1);
	}
}

void PrintBtree(Btree_t* tree) {
	if (tree != NULL && tree->root != NULL)
		PrintNodeBtree(tree->root, 0);
}

static int GetLastInNode(Btree_node_t* node, int index) {
	Btree_node_t* cur = node->children[index];

	while (cur->ifLeaf == FALSE)
		cur = cur->children[cur->numKeys];

	return cur->key[cur->numKeys - 1];
}

static int GetFirstInNode(Btree_node_t* node, int index) {
	Btree_node_t* cur = node->children[index + 1];

	while (cur->ifLeaf == FALSE)
		cur = cur->children[0];

	return cur->key[0];
}

static void Merge(Btree_node_t* node, int index) {
	Btree_node_t* child = node->children[index];
	Btree_node_t* sibling = node->children[index + 1];

	child->key[FACTOR - 1] = node->key[index];

	memcpy(&child->key[FACTOR], &sibling->key[0], sibling->numKeys * sizeof(int));

	if (child->ifLeaf == FALSE)
		memcpy(&child->children[FACTOR], &sibling->children[0], (sibling->numKeys + 1) * sizeof(Btree_node_t*));

	if (node->numKeys > index + 1)
		memmove(&node->key[index], &node->key[index + 1], (node->numKeys - index - 1) * sizeof(int));

	if (node->numKeys > index + 1)
		memmove(&node->children[index + 1], &node->children[index + 2], (node->numKeys - index - 1) * sizeof(Btree_node_t*));

	child->numKeys += sibling->numKeys + 1;
	node->numKeys--;

	free(sibling);
}

static int DeleteNode(Btree_node_t* node, int key) {
	int index;

	if (node == NULL)
		return MY_FAIL;

	index = SearchBin(node->key, node->numKeys, key);
	if (index < node->numKeys && node->key[index] == key) {
		if (node->ifLeaf == TRUE)
			DeleteFromLeaf(node, index);
		else
			DeleteFromNonLeaf(node, index);
	}
	else {
		int ifIndexEqNumKeys = (index == node->numKeys) ? 1 : 0;

		if (node->ifLeaf == TRUE)
			return MY_FAIL;

		if (node->children[index]->numKeys < FACTOR)
			Fill(node, index);

		if (ifIndexEqNumKeys && index > node->numKeys) {
			if (!DeleteNode(node->children[index - 1], key))
				return MY_FAIL;
		}
		else
			if (!DeleteNode(node->children[index], key))
				return MY_FAIL;
	}

	return SUCCESS;
}

static void DeleteFromNonLeaf(Btree_node_t* node, int index) {
	int k = node->key[index];

	if (node->children[index]->numKeys >= FACTOR) {
		int prev = GetLastInNode(node, index);

		node->key[index] = prev;
		DeleteNode(node->children[index], prev);
	}
	else if (node->children[index + 1]->numKeys >= FACTOR) {
		int succ = GetFirstInNode(node, index);

		node->key[index] = succ;
		DeleteNode(node->children[index + 1], succ);
	}
	else {
		Merge(node, index);
		DeleteNode(node->children[index], k);
	}
}

static void DeleteFromLeaf(Btree_node_t* node, int index) {
	if (node->numKeys > index + 1)
		memmove(&node->key[index], &node->key[index + 1], (node->numKeys - index - 1) * sizeof(int));

	node->numKeys--;

	return;
}

static void BorrowFromNext(Btree_node_t* node, int index) {
	Btree_node_t* child = node->children[index];
	Btree_node_t* sibling = node->children[index + 1];

	child->key[child->numKeys] = node->key[index];

	if (child->ifLeaf == FALSE)
		child->children[child->numKeys + 1] = sibling->children[0];

	node->key[index] = sibling->key[0];

	memmove(&sibling->key[0], &sibling->key[1], (sibling->numKeys - 1) * sizeof(int));

	if (sibling->ifLeaf == FALSE)
		memmove(&sibling->children[0], &sibling->children[1], sibling->numKeys * sizeof(Btree_node_t*));

	child->numKeys++;
	sibling->numKeys--;
}

static void BorrowFromPrev(Btree_node_t* node, int index) {
	Btree_node_t* child = node->children[index];
	Btree_node_t* sibling = node->children[index - 1];

	memmove(&child->key[1], &child->key[0], child->numKeys * sizeof(int));

	if (child->ifLeaf == FALSE)
		memmove(&child->children[1], &child->children[0], (child->numKeys + 1) * sizeof(Btree_node_t*));

	child->key[0] = node->key[index - 1];

	if (child->ifLeaf == FALSE)
		child->children[0] = sibling->children[sibling->numKeys];

	node->key[index - 1] = sibling->key[sibling->numKeys - 1];
	child->numKeys++;
	sibling->numKeys--;
}

static void Fill(Btree_node_t* node, int index) {
	if (index != 0 && node->children[index - 1]->numKeys >= FACTOR)
		BorrowFromPrev(node, index);
	else if (index != node->numKeys && node->children[index + 1]->numKeys >= FACTOR)
		BorrowFromNext(node, index);
	else {
		if (index != node->numKeys)
			Merge(node, index);
		else
			Merge(node, index - 1);
	}
}


int DeleteFromBtree(Btree_t* tree, int key) {
	int ifDeleted;
	if (tree == NULL)
		return MY_FAIL;

	ifDeleted = DeleteNode(tree->root, key);

	if (tree->root != NULL) {
		if (tree->root->numKeys == 0) {
			Btree_node_t* tmp = tree->root;

			if (tree->root->ifLeaf == TRUE)
				tree->root = NULL;
			else
				tree->root = tree->root->children[0];

			free(tmp);
		}
	}

	if (!ifDeleted)
		return MY_FAIL;

	return SUCCESS;
}