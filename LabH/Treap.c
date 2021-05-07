#include "Treap.h"

Node* InitNode(int val) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node)
		return NULL;
	new_node->left = new_node->right = NULL;
	new_node->val = val;
	new_node->prior = rand();
	new_node->count = 1;
	return new_node;

}

int GetCount(Node* p) {
	return p ? p->count : 0;
}

void UpdateCount(Node* p) {
	if (p)
		p->count = GetCount(p->left) + GetCount(p->right) + 1;
}

Node* Merge(Node* l, Node* r) {
	Node* res = NULL;
	if (!l)
		res = r;
	else if (!r)
		res = l;
	else if (l->prior > r->prior) {
		l->right = Merge(l->right, r);
		res = l;
	}
	else {
		r->left = Merge(l, r->left);
		res = r;
	}
	UpdateCount(res);
	return res;
}

void Split(int key, Node* root, Node** l, Node** r, int add) {
	if (!root) {
		*l = *r = NULL;
		return;
	}
	int cur_key = GetCount(root->left) + add;
	if (key <= cur_key) {
		Split(key, root->left, l, &(root->left), add);
		*r = root;
	}
	else {
		Split(key, root->right, &(root->right), r, add + 1 + GetCount(root->left));
		*l = root;
	}
	UpdateCount(root);
}

void Insert(int val, int pos, Node** root) {
	Node* new_node = InitNode(val);
	Node* head = NULL;
	Node* tail = NULL;
	if (pos < 0 || !new_node)
		return;
	Split(pos, *root, &head, &tail, DEFAULT_ADD_VAL);
	*root = Merge(Merge(head, new_node), tail);
}

void Print(Node* root) {
	if (!root)
		return;
	Print(root->left);
	printf("%d ", root->val);
	Print(root->right);
}

int Delete(int pos, Node** root) {
	int res = NOT_DELETED;
	Node* pos_elem = NULL;
	Node* head = NULL;
	Node* tail = NULL;
	Node* new_tail = NULL;
	if (pos < 0)
		return res;
	Split(pos, *root, &head, &tail, DEFAULT_ADD_VAL);
	Split(1, tail, &pos_elem, &new_tail, DEFAULT_ADD_VAL);
	if (pos_elem) {
		res = DELETED;
		free(pos_elem);
	}
	*root = Merge(head, new_tail);
	return res;
}

void DeleteTree(Node* root) {
	if (root) {
		DeleteTree((root)->left);
		DeleteTree((root)->right);
		free(root);
		root = NULL;
	}
}

void Check(int val, Node* root, bool* contains) {
	if (root) {
		if (root->val == val)
			*contains = true;
		Check(val, root->left, contains);
		Check(val, root->right, contains);
	}
}

void Find(int val, Node* root, Node** result) {
	if (root && !(*result)) {
		if (root->val == val) {
			*result = root;
		}
		Find(val, root->left, result);
		Find(val, root->right, result);
	}
}

void DeleteVal(int val, Node** root, bool* deleted) {
	
	if (*root && !(*deleted)) {
		if ((*root)->val == val) {
			Node* l = (*root)->left;
			Node* r = (*root)->right;
			free(*root);
			*root = Merge(l, r);
			*deleted = true;
			return;
		}
		DeleteVal(val, &((*root)->left),deleted);
		DeleteVal(val, &((*root)->right),deleted);
	}

}