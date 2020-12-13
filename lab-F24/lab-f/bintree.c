#include "bintree.h"

typedef enum path {
	FROM_PARENT = 10,
	FROM_LEFT_CHILD,
	FROM_RIGHT_CHILD
}PATH_T;

sbtree_t* CreateNode(int l, int r) {
	sec_t* sec = (sec_t*)malloc(sizeof(sec_t));
	sec->l = l;
	sec->r = r;
	sbtree_t* res = (sbtree_t*)malloc(sizeof(sbtree_t));
	res->key = l;
	res->sec = sec;
	//res->rMax = r;
	res->left = NULL;
	res->right = NULL;
	res->p = NULL;

	return res;
}

sbtree_t* SBtreeRMaxFound(sbtree_t* tree){

	return NULL;
}

sbtree_t* SBtreeInsert(sbtree_t* tree, sbtree_t* newEl) {
  sbtree_t* cur = NULL;
	sbtree_t* root = tree;
	sbtree_t* tmp = NULL;
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
	else if (newEl->key < cur->key) {
		cur->left = newEl;
		//Set new rmax
	  /*while (cur != NULL && newEl == cur->left && cur->rMax < newEl->rMax) {
			cur->rMax = newEl->rMax;
			newEl = cur;
			cur = cur->p;
		}*/
	}
	else {
		cur->right = newEl;
		/*tmp = newEl;
		//Set new rmax
		while (cur != NULL && tmp == cur->right) {
			tmp = cur;
			cur = cur->p;
		}
		if (cur != NULL) {
			while (cur != NULL && tmp == cur->left && cur->rMax < newEl->rMax) {
				cur->rMax = newEl->rMax;
				tmp = cur;
				cur = cur->p;
			}
		}*/
	}
	return tree;
}

sbtree_t* SBtreeInsertMod(sbtree_t* tree, int l, int r) {
	sbtree_t* elem = NULL;
	elem = CreateNode(l, r);

	return SBtreeInsert(tree, elem);
}

sbtree_t* SBtreeMin(sbtree_t* tree) {
	while (tree->left != NULL) {
		tree = tree->left;
	}
	return tree;
}

sbtree_t* SBtreeSuccessor(sbtree_t* tree, sbtree_t* elem) {
	sbtree_t* cur = NULL;
	if (elem->right != NULL) {
		return SBtreeMin(elem->right);
	}

	cur = elem->p;
	while ((cur != NULL) && (elem == cur->right)) {
		elem = cur;
		cur = cur->p;
	}

	return cur;
}

sbtree_t* SBtreeDelete(sbtree_t* tree, int l, int r) {
	sbtree_t* toDel = NULL;
	toDel = SBtreeSearch(tree, l, r);

	tree = SBtreeDeletePtr(tree, toDel);

	return tree;
}


sbtree_t* SBtreeDeletePtr(sbtree_t* tree, sbtree_t* toDel) {
	sbtree_t* bfDel = NULL;
	sbtree_t* child = NULL;

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
		bfDel = SBtreeSuccessor(tree, toDel);

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
		toDel->sec = bfDel->sec; 
		//toDel->rMax = bfDel->rMax;
	}
	free(bfDel);
	return tree;
}

sbtree_t* SBtreeSearch(sbtree_t* tree, int l, int r) {
	sbtree_t* cur = tree;

	if (l <= r) {
		while (cur != NULL) {
			if (l < cur->key)
				cur = cur->left;
			else
				if (cur->sec->r == r)
					return cur;
			cur = cur->right;
		}
	}
	return NULL;
}


ERR_STATUS SBtreeSearchMod(sbtree_t* tree, int l, int r) {
	if (l <= r) {
		sbtree_t* cur = tree;

		while (cur != NULL) {
			if (l < cur->key)
				cur = cur->left;
			else
				if (cur->sec->r == r)
					return OK;
				cur = cur->right;
		}
		return ERROR;
	}

	return OK;
}

void SBtreeFree(sbtree_t** tree) {
	if (*tree != NULL) {
		SBtreeFree(&((*tree)->left));
		SBtreeFree(&((*tree)->right));
		free((*tree)->sec);
		free(*tree);
		*tree = NULL;
	}
	return;
}

void PrintTreeBad(sbtree_t* tree, int numSpaces){
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

void SBtreeInorderWalk(sbtree_t* tree) {
	if (tree != NULL) {
		SBtreeInorderWalk(tree->left);
		printf("%i ", tree->key);
		SBtreeInorderWalk(tree->right);
	}
}

void SBtreeInorderWalkR(sbtree_t* tree) {
	if (tree != NULL) {
		SBtreeInorderWalkR(tree->left);
		printf("%i ", tree->sec->r);
		SBtreeInorderWalkR(tree->right);
	}
}

sbtree_t* SBToParent(int* origin, sbtree_t* curP) {
	sbtree_t* cur = curP;

	if (cur->p == NULL) {
		curP = NULL;
		return curP;
	}
	*origin = cur == cur->p->left ? FROM_LEFT_CHILD : FROM_RIGHT_CHILD;
	return cur->p;
}

sbtree_t* SBToLeft(int* origin, sbtree_t* curP) {
	*origin = FROM_PARENT;
	return curP->left;
}

sbtree_t* SBToRight(int* origin, sbtree_t* curP) {
	*origin = FROM_PARENT;
	return curP->right;
}

ERR_STATUS CheckCross(int lUnk, int rUnk, sbtree_t* cur) {
	if (lUnk > rUnk)
		return ERROR;
	if (lUnk > cur->sec->r || rUnk < cur->sec->l)
		return ERROR;
	else
		return OK;
}

sbtree_t** SBtreeInsectSec(sbtree_t* tree, int l, int r) {
	sbtree_t** path = NULL;
	sbtree_t* cur = tree;
	int pathLen = 0;
	int origin = FROM_PARENT;

	while (cur != NULL) {
		switch (origin) {
		case FROM_PARENT:
			if (CheckCross(l, r, cur) == OK) {
				path = (sbtree_t**)realloc(path, sizeof(sbtree_t*) * (pathLen + 1));
				path[pathLen] = cur;
				pathLen++;
			}
			if (cur->left != NULL)
				cur = SBToLeft(&origin, cur);
			else
				origin = FROM_LEFT_CHILD;
			break;

		case FROM_LEFT_CHILD:
			if (cur->right != NULL)
				cur = SBToRight(&origin, cur);
			else
				origin = FROM_RIGHT_CHILD;
			break;

		case FROM_RIGHT_CHILD:
			cur = SBToParent(&origin, cur);
			break;
		}
	}

	path = (sbtree_t**)realloc(path, sizeof(sbtree_t*) * (pathLen + 1));
	path[pathLen] = NULL;
	return path;
}

ERR_STATUS SBTreeInsectSecMod(sbtree_t* tree,int l, int r, int* numOfInsect) {
	sbtree_t** arrOfInsect = NULL;
	int i;

	arrOfInsect = SBtreeInsectSec(tree, l, r);
	for (i = 0; arrOfInsect[i] != NULL; ++i);

	if (i == 0) {
		*numOfInsect = 0;
		return ERROR;
	}

	*numOfInsect = i;
	return OK;
}