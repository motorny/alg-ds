#include "bintree.h"

btree_t* BtreeInsert(btree_t* tree, btree_t* newEl) {
  btree_t* cur = NULL;
	btree_t* root = tree;
	//btree_t* curNod = tree;

	while (root != NULL) {
		cur = root;
		if (newEl->key < cur->key)
			root = root->left;
		else
			root = root->right;
	}

	newEl->p = cur;
	if (cur == NULL)
		tree = newEl; //Empty tree
	else if (newEl->key < cur->key)
		cur->left = newEl;
	else
		cur->right = newEl;

	return BtreeSubHeightDif(tree);
}

btree_t* BtreeInsertMod(btree_t* tree, int key) {
	btree_t* elem = NULL;
	elem = CreateNode(key);

	return BtreeInsert(tree, elem);
}

btree_t* BtreeSearch(btree_t* tree, int key) {
	btree_t* cur = tree;

	while (cur != NULL && cur->key != key) {
		if (key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return cur;
}

btree_t* BtreeMin(btree_t* tree) {
	while (tree->left != NULL) {
		tree = tree->left;
	}
	return tree;
}

btree_t* BtreeSuccessor(btree_t* tree, btree_t* elem) {
	btree_t* cur = NULL;
	if (elem->right != NULL) {
		return BtreeMin(elem->right);
	}

	cur = elem->p;
	while ((cur != NULL) && (elem == cur->right)) {
		elem = cur;
		cur = cur->p;
	}

	return cur;
}

btree_t* BtreeDelete(btree_t* tree, int key) {
	btree_t* toDel = NULL;
	toDel = BtreeSearch(tree, key);

	tree = BtreeDeletePtr(tree, toDel);

	return tree;
}


btree_t* BtreeDeletePtr(btree_t* tree, btree_t* toDel) {
	btree_t* bfDel = NULL;
	btree_t* child = NULL;

	if (toDel == NULL)
		return tree;

	//When toDel have no child. May be replaced in main algorythm
	if (toDel->left == NULL && toDel->right == NULL) {
		if (toDel->p == NULL) {
			free(toDel);
			return NULL;
		}

		if (toDel->p->left == toDel)
			toDel->p->left = NULL;
		else
			toDel->p->right = NULL;

		free(toDel);
		return tree;
	}

	//Detect case
	if (toDel->left == NULL || toDel->right == NULL)
		bfDel = toDel;
	else
		bfDel = BtreeSuccessor(tree, toDel);

	//Found child of bfDel
	if (bfDel->left != NULL)
		child = bfDel->left;
	else
		child = bfDel->right;

	//Creates new parent-child connect
	if (child != NULL)
		child->p = bfDel->p;
  
	//Tell new parent about child or NULL
	if (bfDel->p == NULL)
		tree = child;
	else {
		if (bfDel == bfDel->p->left)
			bfDel->p->left = child;
		else
			bfDel->p->right = child;
	}
	

	//Replace toDel by bfDel
	if(bfDel != toDel){
		toDel->key = bfDel->key;
		toDel->difNods = bfDel->difNods;
	}
	free(bfDel);
	return tree;
}

ERR_STATUS BtreeSearchMod(btree_t* tree, int key) {
	btree_t* cur = tree;

	while (cur != NULL && cur->key != key) {
		if (key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}
	if (cur == NULL)
		return ERROR;

	return OK;
}

void BtreeFree(btree_t** tree) {
	if (*tree != NULL) {
		BtreeFree(&((*tree)->left));
		BtreeFree(&((*tree)->right));
		free(*tree);
		*tree = NULL;
	}
	return;
}

btree_t* CreateNode(int data) {
	btree_t* res = (btree_t*)malloc(sizeof(btree_t));
	res->key = data;
	res->difNods = 0;
	res->left = NULL;
	res->right = NULL;
	res->p = NULL;

	return res;
}

void PrintTreeBad(btree_t* tree, int numSpaces){
	int i;
	if (tree == NULL)
		return;

	PrintTreeBad(tree->right, numSpaces + 1);
	for (i = 0; i < numSpaces; i++) 
		putchar(' ');
	printf("%i\n", tree->key);
	PrintTreeBad(tree->left, numSpaces + 1);

	return;
}

int BtreeHeight(btree_t* tree){
	if (tree == NULL)
		return 0;

	int hLeft = 0;
	int hRight = 0;
	int max;
	if (tree->left != NULL)
		hLeft = BtreeHeight(tree->left);
	else
		hLeft = -1;
	if (tree->right != NULL)
		hRight = BtreeHeight(tree->right);
	else
		hRight = -1;
	max = hLeft > hRight ? hLeft : hRight;

	return max + 1;
}

btree_t* BtreeSubHeightDif(btree_t* tree){
	if (tree != NULL){
		int hLeft = 0;
		int hRight = 0;

		if (tree->left != NULL){
			hLeft = BtreeHeight(tree->left) + 1;
			BtreeSubHeightDif(tree->left);
		}
		if (tree->right != NULL){
			hRight = BtreeHeight(tree->right) + 1;
			BtreeSubHeightDif(tree->right);
		}
		tree->difNods = abs(hLeft - hRight);
	}
	return tree;
}

void BtreeInorderWalk(btree_t* tree) {
	if (tree != NULL) {
		BtreeInorderWalk(tree->left);
		printf("%i ", tree->key);
		BtreeInorderWalk(tree->right);
	}
}

void BtreeInorderWalkSubNods(btree_t* tree) {
	if (tree != NULL) {
		BtreeInorderWalkSubNods(tree->left);
		printf("%i ", tree->difNods);
		BtreeInorderWalkSubNods(tree->right);
	}
}
