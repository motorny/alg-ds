#include <stdlib.h>
#include <stdio.h>
#include "2_3_tree.h"


void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}



node* InitNode(int key) {
	node* new_node = (node*)malloc(sizeof(node));
	if (!new_node) {
		perror("not enough memory\n");
		return NULL;
	}
	new_node->size = 1;
	new_node->key[0] = key;
	new_node->first = NULL;
	new_node->second = NULL;
	new_node->third = NULL;
	new_node->fourth = NULL;
	new_node->parent = NULL;
	return new_node;
}


int IsLeaf(node* p) {
	return (p->first == NULL) && (p->second == NULL) && (p->third == NULL);
}



void Sort(node* p) {
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



void InsertKey(node* p, int key) {
	p->key[p->size] = key;
	p->size++;
	Sort(p);
}



node* Split(node* p) {

	if (p->size < 3)
		return p;

	node* x = InitNode(p->key[0]);
	x->first = p->first;
	x->second = p->second;
	x->parent = p->parent;

	node* y = InitNode(p->key[2]);
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

		node* tmp = p->parent;
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



node* Insert(node* root, int key) {

	if (!root)
		return InitNode(key);

	if (IsLeaf(root))
		InsertKey(root, key);
	else if (key <= root->key[0])
		Insert(root->first, key);
	else if ((root->size == 1) || ((root->size == 2) && key <= root->key[1]))
		Insert(root->second, key);
	else
		Insert(root->third, key);

	return Split(root);
}


int Find(node* p, int key) {
	if (!p)
		return 0;
	for (int i = 0; i < p->size; i++)
		if (p->key[i] == key)
			return 1;
	return 0;
}



node* Search(node* p, int key) {
	if (!p)
		return NULL;

	if (Find(p, key))
		return p;
	else if (key < p->key[0])
		return Search(p->first, key);
	else if ((p->size == 2 && key < p->key[1]) || p->size == 1)
		return Search(p->second, key);
	else if (p->size == 2)
		return Search(p->third, key);
}



node* SearchMin(node* p) {
	if (!p)
		return p;
	if (!(p->first))
		return p;
	return SearchMin(p->first);
}


void RemoveKey(node* p, int key) {
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


node* Redistribute(node* leaf) {
	node* parent = leaf->parent;
	node* first = parent->first;
	node* second = parent->second;
	node* third = parent->third;

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

			RemoveKey(parent, parent->key[0]);

			free(first);

		}
		else if (second == leaf) {

			InsertKey(first, parent->key[0]);
			RemoveKey(parent, parent->key[0]);


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
			RemoveKey(parent, parent->key[1]);

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
				RemoveKey(second, second->key[1]);
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
				RemoveKey(first, first->key[1]);
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
				RemoveKey(third, third->key[0]);

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
				RemoveKey(first, first->key[1]);

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
				RemoveKey(second, second->key[0]);

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
				RemoveKey(third, third->key[0]);
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
			RemoveKey(second, second->key[0]);

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
			RemoveKey(first, first->key[1]);

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



node* Merge(node* leaf) {


	node* parent = leaf->parent;

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

		RemoveKey(parent, parent->key[0]);
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

		RemoveKey(parent, parent->key[0]);

		free(parent->second);
		parent->second = NULL;
	}

	if (parent->parent == NULL) {
		node* tmp = NULL;
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


node* Fix(node* leaf) {

	node* parent = leaf->parent;

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

node* Remove(node* p, int key) {

	node* item = Search(p, key);

	if (!item)
		return NULL;
	node* min = NULL;


	if (item->key[0] == key)
		min = SearchMin(item->second);
	else
		min = SearchMin(item->third);

	if (min) {
		if (key == item->key[0])
			swap(&(item->key[0]), &(min->key[0]));
		else
			swap(&(item->key[1]), &(min->key[0]));
		item = min;
	}

	RemoveKey(item, key);
	return Fix(item);
}

void FreeTree(node* root) {
	if (root) {
		FreeTree(root->first);
		FreeTree(root->second);
		FreeTree(root->third);
		free(root);
	}
}


void PrintLinearly(node* ptr) {
	if (ptr) {
		if (ptr->size >= 1) {
			PrintLinearly(ptr->first);
			printf("%d ", ptr->key[0]);
			PrintLinearly(ptr->second);
			if (ptr->size == 2) {
				printf("%d ", ptr->key[1]);
				PrintLinearly(ptr->third);
			}
		}
	}
}



void ParseCommand(char command, int key, node** root) {
	if (command == 'a') {
		if (!Search(*root, key)) {
			*root = Insert(*root, key);
		}
	}
	else if (command == 'r') {
		if (Search(*root, key)) {
			*root = Remove(*root, key);
		}
	}
	else if (command == 'f') {
		if (Search(*root, key)) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}
	else if (command == 'p') {
		PrintLinearly(*root);
		printf("\n");
	}

}
