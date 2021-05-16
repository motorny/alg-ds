#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable:4996)

#define t 3 //параметр для количества ключей в узле 
#define FALSE 0
#define TRUE 1

typedef struct BNode_t {
	int leaf; //является ли узел листом
	int n; //количество ключей узла
	int keys[2 * t - 1]; //ключи узла
	struct BNode_t* c[2 * t]; //массив указателей на детей
} B_Node;

typedef enum Condition {
	NOT_FOUND,
	SUCCESS,
	NOT_ENOUGH_KEYS,
} Condition;


B_Node* tree = NULL;


//создание нового узла
B_Node* CreateNewNode() {
	B_Node* tempNode = (B_Node*)malloc(sizeof(B_Node));
	if (!tempNode)
		return NULL;
	tempNode->n = 0;
	tempNode->leaf = TRUE;

	for (int i = 0; i < (2 * t); i++)
		tempNode->c[i] = NULL;

	return tempNode;
}


//i - индекс полного узла как сына x
//x - незаполненный узел
//pазбиение узла
void B_Node_Split_Child(B_Node* x, int i) {
	int j;
	B_Node* temp = CreateNewNode();
	B_Node* tempFull = x->c[i]; //заполненный дочерний узел
	

	temp->leaf = tempFull->leaf;
	temp->n = t - 1;

	for (j = 0; j < temp->n; j++)
		temp->keys[j] = tempFull->keys[j + t];

	if (!tempFull->leaf) {
		for (j = 0; j < (temp->n) + 1; j++) {
			temp->c[j] = tempFull->c[j + t];
			tempFull->c[j + t] = NULL;
		}
	}

	tempFull->n = t - 1;

	if (x->c[i + 1] != NULL) {
		j = i + 1;
		while (x->c[j] != NULL)
			j++;

		for (j; j > i + 1; j--) {
			x->c[j] = x->c[j - 1];
			x->keys[j - 1] = x->keys[j - 2];
		}
	}
	x->c[i + 1] = temp;
	x->keys[i] = tempFull->keys[t - 1];
	x->n++;
}

//вставляет ключ k в узел x
void B_Node_Insert_Nonfull(B_Node* x, int k) {
	int i = (x->n) - 1;

	//если лист, добавьте сюда
	if (x->leaf) {
		while (i >= 0 && k < x->keys[i]) {
			x->keys[i + 1] = x->keys[i];
			i--;
		}
		x->keys[i + 1] = k;
		x->n++;
	}
	else {//если не лист, посмотрите на детей
		while (i >= 0 && k < x->keys[i])
			i--;
		i++;

		if (x->c[i]->n == 2 * t - 1) {
			B_Node_Split_Child(x, i);
			if (k > x->keys[i])
				i++;
		}
		B_Node_Insert_Nonfull(x->c[i], k);
	}
}

//найти по ключу
B_Node* KeyFind(B_Node* tree, int key) {
	int i = 0;

	if (!tree)
		return NULL;

	while (i < tree->n && key > tree->keys[i])
		i++;


	if (i < tree->n && key == tree->keys[i])
		return tree;
	else if (tree->leaf)
		return NULL;

	return KeyFind(tree->c[i], key);
}

//добавление по ключу
void KeyInsert(int key, B_Node** tree) {
	B_Node* r = (*tree), * s = NULL;


	//если ключ найден то ничего не делай
	if (KeyFind((*tree), key))
		return;

	//если корень пустой, то создай узел и добавь элемент
	if (!(*tree)) {
		(*tree) = CreateNewNode();
		(*tree)->keys[0] = key;
		(*tree)->n++;
		return;
	}

	//если в корне количество ключей узла достигло максимума
	if (r->n == 2 * t - 1) {
		//создаем новый корень
		s = CreateNewNode();
		(*tree) = s;
		s->leaf = FALSE;
		s->n = 0;
		s->c[0] = r;

		B_Node_Split_Child(s, 0);
		B_Node_Insert_Nonfull(s, key);
	}
	else
		B_Node_Insert_Nonfull(r, key);
}

//нахождение позиции
int FindPosition(int key, int* arr, int n) {
	int temp = 0;
	while (temp < n && key > arr[temp])
		temp++;
	return temp;
}

//удаление
int Remove(B_Node* tree, int key) {
	B_Node** c;
	B_Node* l, * r, * temp, * temp1;
	int pos, i, k, n, min, n1;
	int* arr;
	int val;

	if (!tree)
		return NOT_FOUND;

	n = tree->n;
	arr = tree->keys;
	c = tree->c;
	min = (t - 1) / 2;

	pos = FindPosition(key, arr, n);
	// c это лист
	if (c[0] == NULL) {
		if (pos == n || key < arr[pos])
			return NOT_FOUND;

		for (i = pos + 1; i < n; i++) {
			arr[i - 1] = arr[i];
			c[i] = c[i + 1];
		}
		tree->n--;

		//если дерево является корневым, может быть 1 ключ
		if (tree == tree)
			min = 1;

		if (tree->n >= min)
			return SUCCESS;
		else
			return NOT_ENOUGH_KEYS;
	}

	//c не лист
	if (pos < n && key == arr[pos]) {
		temp = c[pos];
		while (TRUE) {
			n1 = temp->n;
			temp1 = temp->c[n1];
			if (temp1 == NULL)
				break;
			temp = temp1;
		}
		arr[pos] = temp->keys[n1 - 1];
		temp->keys[n1 - 1] = key;
	}
	val = Remove(c[pos], key);
	if (val != NOT_ENOUGH_KEYS)
		return val;

	//если в элементе недостаточно ключей, добавьте
	if (pos > 0 && c[pos - 1]->n > min) {
		k = pos - 1;
		l = c[k];
		r = c[pos];
		r->c[r->n + 1] = r->c[r->n];
		for (i = r->n; i > 0; i--) {
			r->keys[i] = r->keys[i - 1];
			r->c[i] = r->c[i - 1];
		}
		r->n++;
		r->keys[0] = arr[k];
		r->c[0] = l->c[l->n];
		arr[k] = l->keys[--l->n];
		return SUCCESS;
	}

	if (pos < n && c[pos + 1]->n > min) {
		k = pos;
		l = c[k];
		r = c[k + 1];
		l->keys[l->n] = arr[k];
		l->c[l->n + 1] = r->c[0];
		arr[k] = r->keys[0];
		l->n++;
		r->n--;
		for (i = 0; i < r->n; i++) {
			r->keys[i] = r->keys[i + 1];
			r->c[i] = r->c[i + 1];
		}
		r->c[r->n] = r->c[r->n + 1];
		return SUCCESS;
	}

	if (pos == n)
		k = pos - 1;
	else
		k = pos;

	l = c[k];
	r = c[k + 1];

	//слияние 2 детей
	l->keys[l->n] = arr[k];
	l->c[l->n + 1] = r->c[0];
	for (i = 0; i < r->n; i++) {
		l->keys[l->n + 1 + i] = r->keys[i];
		l->c[l->n + 2 + i] = r->c[i + 1];
	}
	l->n = l->n + r->n + 1;

	free(r);
	for (i = pos + 1; i < n; i++) {
		arr[i - 1] = arr[i];
		c[i] = c[i + 1];
	}
	if (tree == tree)
		min = 1;
	tree->n--;
	if (tree->n >= min)
		return SUCCESS;
	else
		return NOT_ENOUGH_KEYS;
}

//удаление по ключу
void KeyRemove(int key) {
	B_Node* oldRoot;
	int val = Remove(tree, key);
	if (val == NOT_ENOUGH_KEYS) {
		oldRoot = tree;
		tree = tree->c[0];
		free(oldRoot);
	}
}

//уничтожение дерева 
void DeleteTree(B_Node* tree) {
	if (!tree)
		return;
	if (!tree->leaf) {
		int i;
		for (i = 0; i <= tree->n; i++)
			DeleteTree(tree->c[i]);
	}
	free(tree);
	return;
}

int main() {
	char command;
	int key;

	while (TRUE) {
		command = fgetc(stdin);

		if (command == EOF || command == '\n') {
			break;
		}

		scanf("%i", &key);
			
		switch (command)
		{
		case'a':
			KeyInsert(key, &tree);
			break;
		case'r':
			KeyRemove(key);
			break;
		case'f':
			if (KeyFind(tree, key))
				printf("yes\n");
			else
				printf("no\n");
			break;
		}


		
		


		key = 0;
		command = fgetc(stdin);
	}

	DeleteTree(tree);
	return 0;
}