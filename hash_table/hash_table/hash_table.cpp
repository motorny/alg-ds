#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



node* init_node(const char* str, int str_len) {
	node* n = (node*)malloc(sizeof(node));
	if (!n)
		return NULL;
	n->str = (char*)malloc(sizeof(char) * str_len);
	if (!(n->str)) {
		free(n);
		return NULL;
	}
	strcpy_s(n->str, str_len, str);
	n->next = NULL;
	return n;
}

int hash_func(const char* str, int table_size) {
	int hash = 0;
	while (*str) {
		hash += *str;
		str++;
	}
	return hash % table_size;
}


node* find_node(hash_table* t, const char* str) {
	if (!t)
		return NULL;
	int key = hash_func(str, t->size);
	if (!(t->table[key]))
		return NULL;
	node* tmp = t->table[key];
	while (tmp) {
		if (strcmp(tmp->str, str) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}


hash_table* init_table(int size, int str_size) {
	hash_table* table = (hash_table*)malloc(sizeof(hash_table));
	table->table = (node**)malloc(size * sizeof(node*));
	table->size = size;

	for (int i = 0; i < size; i++) {
		table->table[i] = NULL;
	}

	return table;
}

//void insert_by_node(node** field, const char* str) {
//	if (!field)
//		return;
//	if (!(*field)) {
//		*field = init_node(str, strlen(str));
//		return;
//	}
//
//	node* temp = *field;
//	node* old = *field;
//	while (temp != NULL)
//	{
//		if (strcmp(temp->str, str) == 0)
//			return;
//		old = temp;
//		temp = temp->next;
//	}
//
//	old->next = init_node(str, strlen(str));
//}
//
//void insert_node(hash_table* t, const char* str) {
//	if (!t)
//		return;
//
//	insert_by_node(&(t->table[hash_func(str, t->size)]), str);
//
//}



void insert_node(hash_table* t, node* new_node) {
	if (!t || !new_node)
		return;
	if (find_node(t, new_node->str) != NULL)
		return;

	int key = hash_func(new_node->str, t->size);
	if (t->table[key] == NULL) {
		t->table[key] = new_node;
	}
	else {
		node* tmp = t->table[key];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void print_table(hash_table* t) {
	if (!t)
		return;
	for (int i = 0; i < t->size; i++) {
		if (t->table[i]) {
			node* tmp = t->table[i];
			while (tmp) {
				printf("_%s_ ", tmp->str);
				tmp = tmp->next;
			}
		}
		printf("\n");
	}

}


void free_table(hash_table* t) {
	if (!t)
		return;
	if (!t->table)
		return;
	for (int i = 0; i < t->size; i++) {
		if (t->table[i]) {
			node* tmp = t->table[i];
			while (tmp) {
				t->table[i] = t->table[i]->next;
				free(tmp->str);
				free(tmp);
				tmp = t->table[i];
			}
		}
	}
	free(t->table);
	free(t);

}




bool remove(hash_table* t, const char* str) {
	if (!t)
		return false;
	int key = hash_func(str, t->size);
	if (!(t->table[key]))
		return false;
	node* cur = t->table[key];
	node* prev = NULL;
	while (cur) {
		if (strcmp(cur->str, str) == 0) {
			if (!prev) {
				t->table[key] = cur->next;
				free(cur->str);
				free(cur);
				return true;
			}
			else {
				prev->next = cur->next;
				free(cur->str);
				free(cur);
				return true;
			}
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}



void insert_str(hash_table* t, const char* str, int str_len) {
	node* new_node = init_node(str, str_len);
	insert_node(t, new_node);
}