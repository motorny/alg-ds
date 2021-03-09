#include "treap.h"

//	cartesian tree with implicit keys
//	operations:
//	insert element at given position
//	delete element from given position
//	merge two trees
//	split tree by index


node* init_node(int val) {
	node* new_node = (node*)malloc(sizeof(node));
	if (!new_node)
		return NULL;
	new_node->left = new_node->right = NULL;
	new_node->val = val;
	new_node->prior = rand();
	new_node->count = 1;
	return new_node;

}

int get_count(node* p) {
	return p ? p->count : 0;
}

void update_count(node* p) {
	if (p)
		p->count = get_count(p->left) + get_count(p->right) + 1;
}





node* merge(node* l, node* r) {
	node* res = NULL;
	if (!l)
		res = r;
	else if (!r)
		res = l;
	else if (l->prior > r->prior) {
		l->right = merge(l->right, r);
		res = l;
	}
	else {
		r->left = merge(l, r->left);
		res = r;
	}
	update_count(res);
	return res;
}

//[0..n]->[0..key-1] + [key..pos];
// add's default value is 0
void split(int key, node* root, node** l, node** r, int add) {
	if (!root) {
		*l = *r = NULL;
		return;
	}
	int cur_key = get_count(root->left) + add;
	if (key <= cur_key) {
		split(key, root->left, l, &(root->left), add);
		*r = root;
	}
	else {
		split(key, root->right, &(root->right), r, add + 1 + get_count(root->left));
		*l = root;
	}
	update_count(root);
}

void insert(int val, int pos, node** root) {
	node* new_node = init_node(val);
	node* head = NULL;
	node* tail = NULL;
	if (pos < 0 || !new_node)
		return;
	split(pos, *root, &head, &tail, DEFAULT_ADD_VAL);
	*root = merge(merge(head, new_node), tail);
}


void print(node* root) {
	if (!root)
		return;
	print(root->left);
	printf("%d ", root->val);
	print(root->right);
}


int del(int pos, node** root) {
	int res = NOTHING_DELETED;
	node* pos_elem = NULL;
	node* head = NULL;
	node* tail = NULL;
	node* new_tail = NULL;
	if (pos < 0)
		return res;
	split(pos, *root, &head, &tail, DEFAULT_ADD_VAL);
	split(1, tail, &pos_elem, &new_tail, DEFAULT_ADD_VAL);
	if (pos_elem) {
		res = SOMETHING_DELETED;
		free(pos_elem);
	}
	*root = merge(head, new_tail);
	return res;
}


void free_tree(node* root) {
	if (root) {
		free_tree((root)->left);
		free_tree((root)->right);
		free(root);
		root = NULL;
	}
}


void check(int val, node* root, bool* contains) {
	if (root) {
		if (root->val == val)
			*contains = true;
		check(val, root->left, contains);
		check(val, root->right, contains);
	}
}


void find(int val, node* root, node** result) {
	if (root && !(*result)) { // !result not to call function if node's already found earlier
		if (root->val == val) {
			*result = root;
		}
		find(val, root->left, result);
		find(val, root->right, result);
	}
}


void del_val(int val, node** root, bool* deleted) {
	
	if (*root && !(*deleted)) {
		if ((*root)->val == val) {
			node* l = (*root)->left;
			node* r = (*root)->right;
			free(*root);
			*root = merge(l, r);
			*deleted = true;
			return;
		}
		del_val(val, &((*root)->left),deleted);
		del_val(val, &((*root)->right),deleted);
	}

}











//void del_val(int val, node** root) {
//		
//		
//	if (*root && (*root)->val == val) {
//		node* l = (*root)->left;
//		node* r = (*root)->right;
//		free(*root);
//		*root = merge(l, r);
//		return;
//	}
//		
//		
//	node* del_node = NULL;
//	find(val, *root, &del_node);
//	if (del_node) {
//		node* l = (del_node)->left;
//		node* r = (del_node)->right;
//		free(del_node);
//		del_node = merge(l, r);
//	}
//}