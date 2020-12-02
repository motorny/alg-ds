#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable: 4996)

typedef struct node_t {
	int elem;
	struct node_t* left;
	struct node_t* right;
	struct node_t* parent;
}node_t;


char* readString() {
	char* str = NULL, * ptr = NULL;
	int i = 0;
	str = (char*)malloc(2 * sizeof(char));
	if (!str)
		return NULL;
	while ((str[i] = fgetc(stdin)) != EOF) {
		i++;
		ptr = realloc(str, (i + 1) * sizeof(char));
		if (ptr)
			str = ptr;
		else
			return NULL;
	}
	str[i] = 0;
	return str;
}

node_t* getNode(node_t* parent, int elem) {
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	if (tmp) {
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->parent = parent;
		tmp->elem = elem;
	}
	return tmp;
}
void treeDestroy(node_t* tree) {
	if (tree) {
		treeDestroy(tree->left);
		treeDestroy(tree->right);
		free(tree);
	}
}

void nodeAdd(node_t** root, int elem) {

	if ((*root) == NULL) {
		(*root) = getNode(NULL, elem);
		return;
	}
	node_t* tmp = (*root);
	while (tmp) {
		if (elem > tmp->elem) {
			if (tmp->right) {
				tmp = tmp->right;
				continue;
			}
			else {
				tmp->right = getNode(tmp, elem);
				return;
			}
		}
		else if (elem < tmp->elem) {
			if (tmp->left) {
				tmp = tmp->left;
				continue;
			}
			else {
				tmp->left = getNode(tmp, elem);
				return;
			}
		}
		else if (elem == tmp->elem)
			return;
	}

}

node_t* findNode(node_t* root, int elem) {
	while (root) {
		if (elem > root->elem) {
			root = root->right;
			continue;
		}
		else if (elem < root->elem) {
			root = root->left;
		}
		else {
			return root;
		}
	}
	return NULL;
}



void deleteNodeByElem(node_t** root, int elem) {
	node_t* tmp = NULL;
	node_t** lmx;
	if (root) {
		while (*root) {
			if (elem > (*root)->elem) {
				(root) = &((*root)->right);
			}
			else if (elem < (*root)->elem) {
				(root) = &((*root)->left);
			}
			else {
				tmp = (*root);
				if (!(*root)->left && !(*root)->right)
					(*root) = NULL;
				else if (!(*root)->left)
					(*root) = (*root)->right;
				else if (!(*root)->right)
					(*root) = (*root)->left;
				else {
					lmx = &(*root)->left;
					while ((*lmx)->right)
						lmx = &(*lmx)->right;
					(*root)->elem = (*lmx)->elem;
					tmp = *lmx;
					(*lmx) = (*lmx)->left;
				}

				free(tmp);
			}

		}
	}
}


int main(void) {
	char* str = readString(), * tstr, sym = 0;
	int numb = -1, i = 0;


	node_t* tree = NULL;
	tstr = strtok(str, "\n");
	while (tstr != NULL) {
		if (sscanf(tstr + i++, "%c", &sym));
		if (sscanf(tstr + i, "%i", &numb));
		i = 0;
		switch (sym)
		{
		case 'a':
			nodeAdd(&tree, numb);
			break;
		case 'f':
			if (findNode(tree, numb))
				printf("yes\n");
			else
				printf("no\n");
			break;
		case 'r':
			deleteNodeByElem(&tree, numb);
			break;
		}
		tstr = strtok(NULL, "\n");
	}

	free(str);
	treeDestroy(tree);
	return 0;
}



