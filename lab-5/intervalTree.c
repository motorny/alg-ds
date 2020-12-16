#include "intervalTree.h"

tree_t* CreateNode(tree_t* parent, int left, int right) {
	tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
	if (!tree)
		return MEMORY_WAS_NOT_ALLOCATED;

	tree->leftBorder = left;
	tree->rightBorder = right;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = parent;

	return tree;
}

int AddByLeftBorder(tree_t** tree, int left, int right) {
	if (left > right)
		return ERROR;

	if ((*tree) == NULL) {
		(*tree) = CreateNode((tree_t*)NULL, left, right);
		if (!(*tree))
			return ERROR;

	}

	tree_t* current = (*tree);
	while (current != NULL) {
		if (left < current->leftBorder) {
			if (!(current->left)) {
				current->left = CreateNode(current, left, right);
				if (!current)
					return ERROR;
			}
			else {
				current = current->left;
			}
		}
		else if (left > current->leftBorder || ((left == current->leftBorder) && (right != current->rightBorder))) {
			if (!(current->right)) {
				current->right = CreateNode(current, left, right);
				if (!current)
					return ERROR;
			}
			else
				current = current->right;
		}
		else if (current->leftBorder == left && current->rightBorder == right) //is already exist
			return NOT_FINISHED;
	}
	return FINISHED;
}

tree_t* FindByBorders(tree_t* tree, int left, int right) {
	if (!tree || left > right)
		return INCORRECT_INPUT;

	tree_t* current = tree;
	while (current) {
		if (left < current->leftBorder) {
			current = current->left;
		}
		else if (left > current->leftBorder) {
			current = current->right;
		}
		else if (right != current->rightBorder) {
			current = current->right;
		}
		else
			return current;
	}
	return NOT_FOUND;
}

void EquateNodes(tree_t* deleted, tree_t* newSon) {
	deleted->leftBorder = newSon->leftBorder;
	deleted->rightBorder = newSon->rightBorder;
	return;
}

int DeleteByBorders(tree_t* needed) {
	if (!needed)
		return ERROR;

	tree_t* temp = needed;

	//temp is a leaf
	if (temp->left == NULL && temp->right == NULL) {
		if (temp->parent->left == temp)
			temp->parent->left = NULL;
		else
			temp->parent->right = NULL;

	}

	// only one son
	else if (temp->left == NULL && temp->right != NULL) {
		EquateNodes(temp, temp->right);
		if (temp->parent->left == temp) {
			temp->parent->left = temp->right;
		}
		else {
			temp->parent->right = temp->right;
		}

		temp->right->parent = temp->parent;

	}
	else if (temp->right == NULL && temp->left != NULL) {
		EquateNodes(temp, temp->left);
		if (temp->parent->left == temp) {
			temp->parent->left = temp->left;
			
		}
		else {
			temp->parent->right = temp->left;
		}

		temp->left->parent = temp->parent;

	}

	// both sons
	else if (temp->left != NULL && temp->right != NULL) {
		temp = temp->left; //find the rightmost in the left subtree
		while (temp->right != NULL)
			temp = temp->right;

		EquateNodes(needed, temp);

		// left son or none
		if (temp->left == NULL) {
			if(temp->parent->left == temp) //there is one node in the left subtree
				temp->parent->left = NULL;
			else
				temp->parent->right = NULL;
		}
		else if (temp->left != NULL) {
			if (temp->parent->left == temp) //left subtree without right subtree
				temp->parent->left = temp->left;
			else
				temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		}
	}

	free(temp);
	return FINISHED;
}

int DestroyTree(tree_t* tree) {
	if (!tree)
		return ERROR;

	tree->leftBorder = 0;
	tree->rightBorder = 0;
	DestroyTree(tree->left);
	DestroyTree(tree->right);
	free(tree);

	return FINISHED;
}

int WriteAnswer(int left, int right, answer_t* answer) {
	segment_t* segments1 = NULL;
	answer->segments[answer->count].leftBorder = left;
	answer->segments[answer->count].rightBorder = right;
	answer->count++;

	segments1 = (segment_t*)realloc(answer->segments, sizeof(segment_t) * (answer->count + 1));
	if (!segments1)
		return ERROR;

	answer->segments = segments1;
	segments1 = NULL;
	return FINISHED;
}

int IntersectionCheck(tree_t* tree, int left, int right, answer_t* answer) {
	if (left <= tree->leftBorder && right >= tree->rightBorder)
		WriteAnswer(tree->leftBorder, tree->rightBorder, answer);
	else if (tree->leftBorder <= left && tree->rightBorder >= right)
		WriteAnswer(tree->leftBorder, tree->rightBorder, answer);
	else if (tree->leftBorder <= left && right >= tree->rightBorder && left <= tree->rightBorder)
		WriteAnswer(tree->leftBorder, tree->rightBorder, answer);
	else if (left <= tree->leftBorder && right <= tree->rightBorder && right >= tree->leftBorder)
		WriteAnswer(tree->leftBorder, tree->rightBorder, answer);
	else
		return NOT_FINISHED;
	
	return FINISHED;
}

int SearchIntersecting(tree_t* tree, int left, int right, answer_t* answer) {
	tree_t* prevNode = NULL;
	int flag = NOT_FINISHED;
	while (tree) {
		if (prevNode == tree->parent) {
			if (tree->left != NULL) {
				prevNode = tree;
				tree = tree->left;
				continue;
			}
			else
				prevNode = NULL;
		}
		if (prevNode == tree->left) {
			flag += IntersectionCheck(tree, left, right, answer);
			if (tree->right != NULL) {
				prevNode = tree;
				tree = tree->right;
				continue;
			}
			else
				prevNode = NULL;
		}
		if (prevNode == tree->right) {
			prevNode = tree;
			tree = tree->parent;
		}
	}
	if (flag == NOT_FINISHED)
		return NOT_FINISHED;
	return FINISHED;
}

void PrintAnswer(answer_t* answer) {
	for (int i = 0; i < answer->count; i++)
		printf("[%d, %d]  ", answer->segments[i].leftBorder, answer->segments[i].rightBorder);
	printf("\n");
	return;
}

int FreeAnswer(answer_t* answer) {
	if (!answer)
		return ERROR;

	free(answer->segments);
	free(answer);
	return FINISHED;
}

//inner tree traversal
void PrintTree(tree_t* tree) {
	tree_t* prevNode = NULL;
	while (tree) {
		if (prevNode == tree->parent) {
			if (tree->left != NULL) {
				prevNode = tree;
				tree = tree->left;
				continue;
			}
			else
				prevNode = NULL;
		}
		if (prevNode == tree->left) {
			printf("[%d  %d]\n", tree->leftBorder, tree->rightBorder);
			if (tree->right != NULL) {
				prevNode = tree;
				tree = tree->right;
				continue;
			}
			else
				prevNode = NULL;
		}
		if (prevNode == tree->right) {
			prevNode = tree;
			tree = tree->parent;
		}
	}
	return;
}