// red-black tree

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)



typedef struct Node_ {
	struct Node_* left;
	struct Node_* right;
	struct Node_* parent;
	int color; // 1 - black, 0 - red 
	int key;
}Node;


#define NIL &sentinel
static Node sentinel = {NIL, NIL, 0, 1, 0};

static Node* root = NIL;



void LeftRotate(Node* x) {
	Node* y = x->right;
	x->right = y->left;
	if (y->left != NIL)
		y->left->parent = x;

	if (y != NIL)
		y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else {
		root = y;
	}

	y->left = x;
	if (x != NIL)
		x->parent = y;
}

void RightRotate(Node* x) {
	Node* y = x->left;
	x->left = y->right;
	if (y->right != NIL)
		y->right->parent = x;

	if (y != NIL)
		y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else {
		root = y;
	}

	y->right = x;
	if (x != NIL)
		x->parent = y;
}



void InsertFixup(Node* x) {

	while (x != root && x->parent->color == 0) { 

		if (x->parent == x->parent->parent->left) {
			Node* y = x->parent->parent->right;

			if (y->color == 0) {
				x->parent->color = 1;
				y->color = 1;
				x->parent->parent->color = 0;
				x = x->parent->parent;
			}
			else {

				if (x == x->parent->right) {
					x = x->parent;
					LeftRotate(x);
				}

				x->parent->color = 1;
				x->parent->parent->color = 0;
				RightRotate(x->parent->parent);
			}

		}
		else {

			Node* y = x->parent->parent->left;

			if (y->color == 0) {
				x->parent->color = 1;
				y->color = 1;
				x->parent->parent->color = 0;
				x = x->parent->parent;
			}
			else {

				if (x == x->parent->left) {
					x = x->parent;
					RightRotate(x);
				}

				x->parent->color = 1;
				x->parent->parent->color = 0;
				LeftRotate(x->parent->parent);
			}

		}

	}

	root->color = 1;
}


Node* Insert(int data) {

	Node* parent = NULL; 
	Node* current = root;
	Node* x; 

	if (current == NULL)
		return NULL;

	while (current != NIL) {

		if (data == current->key)
			return current;
		parent = current;
		if (data < current->key)
			current = current->left;
		else
			current = current->right;
	}


	x = (Node*)malloc(sizeof(Node));

	if (x == NULL) { 
		printf("insufficient memory (insertNode)\n");
		exit(1);
	}

	x->parent = parent;
	x->key = data;
	x->right = NIL;
	x->left = NIL;
	x->color = 0;

	if (parent) {
		if(data < parent->key)
			parent->left = x;
		else
			parent->right = x;
	}
	else {
		root = x;
	}

	InsertFixup(x);
	return root;

}



Node* FindNode(int data) {

	Node* y = root;

	while (y != NIL) {

		if (data == y->key) {
			//printf("yes\n");
			return y;
		}
		else if (data < y->key)
			y = y->left;
		else
			y = y->right;

		//printf("no\n");
		//return NULL;
	}

	return NULL;
}




void DeleteFixup(Node* x) {
	while (x != root && x->color == 1) {
		if (x == x->parent->left) {
			Node* w = x->parent->right;
			if (w->color == 0) {
				w->color = 1;
				x->parent->color = 0;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 1 && w->right->color == 1) {
				w->color = 0;
				x = x->parent;
			}
			else {
				if (w->right->color == 1) {
					w->left->color = 1;
					w->color = 0;
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->right->color = 1;
				LeftRotate(x->parent);
				x = root;
			}
		}
		else {
			Node* w = x->parent->left;
			if (w->color == 0) {
				w->color = 1;
				x->parent->color = 0;
				RightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 1 && w->left->color == 1) {
				w->color = 0;
				x = x->parent;
			}
			else {
				if (w->left->color == 1) {
					w->right->color = 1;
					w->color = 0;
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->left->color = 1;
				RightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 1;
}





void Delete(int data) {
	Node* x, * y, * z;
	z = FindNode(data);
	if (!z || z == NIL)
		return ;

	if (z->left == NIL || z->right == NIL) {
		y = z;
	}
	else {
		y = z->right;
		while (y->left != NIL)
			y = y->left;
	}

	if (y->left != NIL)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;
	if (y->parent) {
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	else {
		root = x;
	}

	if (y != z)
		z->key = y->key;
	if (y->color == 1)
		DeleteFixup(x);

	free(y);
}



/*int main(void) {

	char comand;
	int key = 0;

	while (1) {

		comand = fgetc(stdin);

		if (comand == EOF || comand == '\n')
			break;

		scanf("%i", &key);

		if (comand == 'a') {
			if (FindNode(key)) {
				//printf("Tree already has this key \n");
			}
			else {
				Insert(key);
			}
		}
		else if (comand == 'r') {

			if (FindNode(key)) {
				Delete(key);
				//printf("Tree don't have this key");
			}
			else {
				//Delete(key);
				//printf("Tree don't have this key");
			}
		}
		else if (comand == 'f') {

			if (FindNode(key)) 
				printf("yes\n");
			else
				printf("no\n");
			
		}

		key = 0;
		comand = fgetc(stdin);
	}

	return 0;
}*/

