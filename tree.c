#include "tree.h"

node_t* InitNode(int key) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	if (!node)
		return NULL;
	node->size = 1;
	node->key[0] = key;
	node->first = NULL;
	node->second = NULL;
	node->third = NULL;
	node->fourth = NULL;
	node->parent = NULL;
	return node;
}

int IsLeaf(node_t* p) {
	return (p->first == NULL) && (p->second == NULL) && (p->third == NULL);
}

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void Sort(node_t* p) {
	int tmp;
	if (p->size == 1)
		return;
	else if (p->size == 2) {
		if (p->key[0] > p->key[1]) {
			tmp = p->key[0];
			p->key[0] = p->key[1];
			p->key[1] = tmp;
		}
	}

	else if (p->size == 3) {
		if (p->key[0] > p->key[1]) {
			tmp = p->key[0];
			p->key[0] = p->key[1];
			p->key[1] = tmp;
		}
		if (p->key[0] > p->key[2]) {
			tmp = p->key[0];
			p->key[0] = p->key[2];
			p->key[2] = tmp;
		}
		if (p->key[1] > p->key[2]) {
			tmp = p->key[1];
			p->key[1] = p->key[2];
			p->key[2] = tmp;
		}
	}
}



void InsertKey(node_t* p, int key) {
	p->key[p->size] = key;
	p->size++;
	Sort(p);
}



node_t* Split(node_t* p) {
	if (p->size < 3)
		return p;

	node_t* x = InitNode(p->key[0]);
	x->first = p->first;
	x->second = p->second;
	x->parent = p->parent;

	node_t* y = InitNode(p->key[2]);
	y->first = p->third;
	y->second = p->fourth;
	y->parent = p->parent;

	if (x->first) x->first->parent = x;
	if (x->second) x->second->parent = x;
	if (y->first) y->first->parent = y;
	if (y->second) y->second->parent = y;

	if (p->parent) {
		InsertKey(p->parent, p->key[1]);

		if (p->parent->first == p)
			p->parent->first = NULL;
		else if (p->parent->second == p)
			p->parent->second = NULL;
		else if (p->parent->third == p)
			p->parent->third = NULL;

		if (p->parent->first == NULL) {
			p->parent->fourth = p->parent->third;
			p->parent->third = p->parent->second;
			p->parent->second = y;
			p->parent->first = x;
		}
		else if (p->parent->second == NULL) {
			p->parent->fourth = p->parent->third;
			p->parent->third = y;
			p->parent->second = x;
		}
		else {
			p->parent->fourth = y;
			p->parent->third = x;
		}

		node_t* tmp = p->parent;
		free(p);
		return tmp;
	}
	else {

		x->parent = p;
		y->parent = p;

		p->key[0] = p->key[1];
		p->first = x;
		p->second = y;
		p->third = NULL;
		p->fourth = NULL;
		p->parent = NULL;
		p->size = 1;

		return p;
	}
}



node_t* AddElem(node_t* root, int key) {

	if (!root)
		return InitNode(key);

	if (IsLeaf(root))
		InsertKey(root, key);
	else if (key <= root->key[0])
		AddElem(root->first, key);
	else if ((root->size == 1) || ((root->size == 2) && key <= root->key[1]))
		AddElem(root->second, key);
	else
		AddElem(root->third, key);

	return Split(root);
}


int Find(node_t* p, int key) {
	if (!p)
		return 0;
	for (int i = 0; i < p->size; i++)
		if (p->key[i] == key)
			return 1;
	return 0;
}



node_t* FindElem(node_t* p, int key) {
	if (!p)
		return NULL;

	if (Find(p, key))
		return p;
	else if (key < p->key[0])
		return FindElem(p->first, key);
	else if ((p->size == 2 && key < p->key[1]) || p->size == 1)
		return FindElem(p->second, key);
	else if (p->size == 2)
		return FindElem(p->third, key);
}



node_t* FindMin(node_t* p) {
	if (!p)
		return p;
	if (!(p->first))
		return p;
	return FindMin(p->first);
}


void Remove(node_t* p, int key) {
	if (p->size >= 1 && p->key[0] == key) {
		p->key[0] = p->key[1];
		p->key[1] = p->key[2];
		p->size--;
	}
	else if (p->size == 2 && p->key[1] == key) {
		p->key[1] = p->key[2];
		p->size--;
	}
}


node_t* Redistribute(node_t* leaf) {
	node_t* parent = leaf->parent;
	node_t* first = parent->first;
	node_t* second = parent->second;
	node_t* third = parent->third;

	if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {

		if (first == leaf) {
			parent->first = parent->second;
			parent->second = parent->third;
			parent->third = NULL;
			InsertKey(parent->first, parent->key[0]);
			parent->first->third = parent->first->second;
			parent->first->second = parent->first->first;

			if (leaf->first != NULL)
				parent->first->first = leaf->first;
			else if (leaf->second != NULL)
				parent->first->first = leaf->second;

			if (parent->first->first != NULL)
				parent->first->first->parent = parent->first;

			Remove(parent, parent->key[0]);

			free(first);

		}
		else if (second == leaf) {

			InsertKey(first, parent->key[0]);
			Remove(parent, parent->key[0]);


			if (leaf->first != NULL)
				first->third = leaf->first;
			else if (leaf->second != NULL)
				first->third = leaf->second;

			if (first->third != NULL)
				first->third->parent = first;

			parent->second = parent->third;
			parent->third = NULL;

			free(second);

		}
		else if (third == leaf) {

			InsertKey(second, parent->key[1]);
			parent->third = NULL;
			Remove(parent, parent->key[1]);

			if (leaf->first != NULL)
				second->third = leaf->first;
			else if (leaf->second != NULL)
				second->third = leaf->second;

			if (second->third != NULL)
				second->third->parent = second;

			free(third);
		}
	}
	else if ((parent->size == 2) && ((first->size == 2) ||
		(second->size == 2) || (third->size == 2))) {

		if (third == leaf) {

			if (leaf->first != NULL) {
				leaf->second = leaf->first;
				leaf->first = NULL;
			}

			InsertKey(leaf, parent->key[1]);

			if (second->size == 2) {
				parent->key[1] = second->key[1];
				Remove(second, second->key[1]);
				leaf->first = second->third;
				second->third = NULL;

				if (leaf->first != NULL)
					leaf->first->parent = leaf;

			}
			else if (first->size == 2) {

				parent->key[1] = second->key[0];
				leaf->first = second->second;
				second->second = second->first;

				if (leaf->first != NULL)
					leaf->first->parent = leaf;

				second->key[0] = parent->key[0];
				parent->key[0] = first->key[1];
				Remove(first, first->key[1]);
				second->first = first->third;

				if (second->first != NULL)
					second->first->parent = second;

				first->third = NULL;

			}
		}
		else if (second == leaf) {

			if (third->size == 2) {

				if (leaf->first == NULL) {
					leaf->first = leaf->second;
					leaf->second = NULL;
				}

				InsertKey(second, parent->key[1]);
				parent->key[1] = third->key[0];
				Remove(third, third->key[0]);

				second->second = third->first;

				if (second->second != NULL)
					second->second->parent = second;

				third->first = third->second;
				third->second = third->third;
				third->third = NULL;
			}
			else if (first->size == 2) {

				if (leaf->second == NULL) {
					leaf->second = leaf->first;
					leaf->first = NULL;
				}

				InsertKey(second, parent->key[0]);
				parent->key[0] = first->key[1];
				Remove(first, first->key[1]);

				second->first = first->third;
				if (second->first != NULL)
					second->first->parent = second;
				first->third = NULL;

			}
		}
		else if (first == leaf) {

			if (leaf->first == NULL) {
				leaf->first = leaf->second;
				leaf->second = NULL;
			}

			InsertKey(first, parent->key[0]);

			if (second->size == 2) {
				parent->key[0] = second->key[0];
				Remove(second, second->key[0]);

				first->second = second->first;

				if (first->second != NULL)
					first->second->parent = first;

				second->first = second->second;
				second->second = second->third;
				second->third = NULL;

			}
			else if (third->size == 2) {
				parent->key[0] = second->key[0];
				second->key[0] = parent->key[1];
				parent->key[1] = third->key[0];
				Remove(third, third->key[0]);
				first->second = second->first;

				if (first->second != NULL)
					first->second->parent = first;

				second->first = second->second;
				second->second = third->first;

				if (second->second != NULL)
					second->second->parent = second;

				third->first = third->second;
				third->second = third->third;
				third->third = NULL;

			}

		}

	}
	else if (parent->size == 1) {

		InsertKey(leaf, parent->key[0]);

		if (first == leaf && second->size == 2) {
			parent->key[0] = second->key[0];
			Remove(second, second->key[0]);

			if (leaf->first == NULL)
				leaf->first = leaf->second;

			leaf->second = second->first;
			second->first = second->second;
			second->second = second->third;
			second->third = NULL;

			if (leaf->second != NULL)
				leaf->second->parent = leaf;

		}
		else if (second == leaf && first->size == 2) {
			parent->key[0] = first->key[1];
			Remove(first, first->key[1]);

			if (leaf->second == NULL)
				leaf->second = leaf->first;

			leaf->first = first->third;
			first->third = NULL;

			if (leaf->first != NULL)
				leaf->first->parent = leaf;
		}
	}

	return parent;
}



node_t* Merge(node_t* leaf) {


	node_t* parent = leaf->parent;

	if (parent->first == leaf) {
		InsertKey(parent->second, parent->key[0]);
		parent->second->third = parent->second->second;
		parent->second->second = parent->second->first;

		if (leaf->first != NULL)
			parent->second->first = leaf->first;
		else if (leaf->second != NULL)
			parent->second->first = leaf->second;

		if (parent->second->first != NULL)
			parent->second->first->parent = parent->second;

		Remove(parent, parent->key[0]);
		free(parent->first);
		parent->first = NULL;

	}
	else if (parent->second == leaf) {
		InsertKey(parent->first, parent->key[0]);

		if (leaf->first != NULL)
			parent->first->third = leaf->first;
		else if (leaf->second != NULL)
			parent->first->third = leaf->second;

		if (parent->first->third != NULL)
			parent->first->third->parent = parent->first;

		Remove(parent, parent->key[0]);

		free(parent->second);
		parent->second = NULL;
	}

	if (parent->parent == NULL) {
		node_t* tmp = NULL;
		if (parent->first != NULL)
			tmp = parent->first;
		else
			tmp = parent->second;

		tmp->parent = NULL;
		free(parent);
		return tmp;
	}

	return parent;
}


node_t* Fix(node_t* leaf) {

	node_t* parent = leaf->parent;

	if (leaf->size == 0 && leaf->parent == NULL) {
		free(leaf);
		return NULL;
	}

	if (leaf->size) {
		if (leaf->parent)
			return Fix(leaf->parent);
		else return leaf;
	}

	if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2)
		leaf = Redistribute(leaf);
	else if (parent->size == 2 && parent->third->size == 2)
		leaf = Redistribute(leaf);
	else
		leaf = Merge(leaf);


	return Fix(leaf);
}

node_t* RemoveNode(node_t* p, int key) {

	node_t* item = FindElem(p, key);

	if (!item)
		return NULL;
	node_t* min = NULL;


	if (item->key[0] == key)
		min = FindMin(item->second);
	else
		min = FindMin(item->third);

	if (min) {
		if (key == item->key[0])
			Swap(&(item->key[0]), &(min->key[0]));
		else
			Swap(&(item->key[1]), &(min->key[0]));
		item = min;
	}

	Remove(item, key);
	return Fix(item);
}

void FreeTree(node_t* root) {
	if (root) {
		FreeTree(root->first);
		FreeTree(root->second);
		FreeTree(root->third);
		free(root);
	}
}


void Print(node_t* ptr) {
	if (ptr) {
		if (ptr->size >= 1) {
			Print(ptr->first);
			printf("%d ", ptr->key[0]);
			Print(ptr->second);
			if (ptr->size == 2) {
				printf("%d ", ptr->key[1]);
				Print(ptr->third);
			}
		}
	}
}



void MainFunc(char command, int key, node_t** root) {
	if (command == 'a') {
		if (!FindElem(*root, key)) {
			*root = AddElem(*root, key);
		}
	}
	else if (command == 'r') {
		if (FindElem(*root, key)) {
			*root = RemoveNode(*root, key);
		}
	}
	else if (command == 'f') {
		if (FindElem(*root, key)) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}
	else if (command == 'p') {
		Print(*root);
		printf("\n");
	}

}