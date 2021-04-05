#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

struct Node {
	int size;
	int key[3];
	struct Node* first;
	struct Node* second;
	struct Node* third;
	struct Node* fourth;
	struct Node* parent;
};



// Создание корня 2-3 дерева
struct Node* CreateNode(int key) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->size = 1;
	newNode->key[0] = key;
	newNode->first = NULL;
	newNode->second = NULL;
	newNode->third = NULL;
	newNode->fourth = NULL;
	newNode->parent = NULL;
	return newNode;
}


// Является ли узел листом
int IsLeaf(struct Node* p) {
	return (p->first == NULL) && (p->second == NULL) && (p->third == NULL);
}



// Сортировка ключей в узле
void Sort(struct Node* p) {
	int tmp;
	if (p->size == 1) return;
	if (p->size == 2) {
		if (p->key[0] > p->key[1]) {
			tmp = p->key[0];
			p->key[0] = p->key[1];
			p->key[1] = tmp;
		}
	}
	
	if (p->size == 3) {
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



void InsertToNode(struct Node* p, int key) {
	p->key[p->size] = key;
	p->size++;
	Sort(p);
}



struct Node* Split(struct Node* p) {

	if (p->size < 3) return p;

	// Создаем две новые вершины, котрые имеют такого же родителя, как и разделяющиеся элемент
	struct Node* x = CreateNode(p->key[0]);
	x->first = p->first;
	x->second = p->second;
	x->parent = p->parent;

	struct Node* y = CreateNode(p->key[2]);
	y->first = p->third;
	y->second = p->fourth;
	y->parent = p->parent;

	if (x->first) x->first->parent = x;
	if (x->second) x->second->parent = x;
	if (y->first) y->first->parent = y;
	if (y->second) y->second->parent = y;

	if (p->parent) {
		InsertToNode(p->parent, p->key[1]);

		if (p->parent->first == p) 
			p->parent->first = NULL;
		else if (p->parent->second == p) 
			p->parent->second = NULL;
		else if (p->parent->third == p)
			p->parent->third = NULL;

		// Сортировка, она же вставка двух узлов вместо ожного
		if (p->parent->first == NULL) {
			p->parent->fourth = p->parent->third;
			p->parent->third = p->parent->second;
			p->parent->second = y;
			p->parent->first = x;
		}
		else if (p->parent->second == NULL){
			p->parent->fourth = p->parent->third;
			p->parent->third = y;
			p->parent->second = x;
		}
		else {
			p->parent->fourth = y;
			p->parent->third = x;
		}

		struct Node* tmp = p->parent;
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



// Вставка ключа
struct Node* Insert(struct Node* root, int key) {

	// Если дерево пусто, то создаем первую вершину (корень) 2-3 дерева
	if (!root)
		return CreateNode(key);

	if (IsLeaf(root))
		InsertToNode(root, key);
	else if (key <= root->key[0])
		Insert(root->first, key);
	else if ((root->size == 1) || ((root->size == 2) && key <= root->key[1]))
		Insert(root->second, key);
	else
		Insert(root->third, key);

	return Split(root);
}

// Высота дерева
int LenTree(struct Node* p) {
	int i = 0;
	struct Node* tmp = p;
	while (tmp != NULL) {
		i++;
		tmp = tmp->first;
	}
	free(tmp);
	return i;
}


// Печать дерева
void PrintTree(struct Node* p, int n) {
	int i;
	if (p != NULL) {
		PrintTree(p->third, n + 1);
		for (i = 0; i < n; i++) putchar(' ');

		PrintTree(p->second, n + 1);
		for (i = 0; i < n; i++) putchar(' ');

		if(p->size == 1)
			printf("%i\n", p->key[0]);
		else if (p->size == 2)
			printf("%i %i\n", p->key[0], p->key[1]);

		//PrintTree(p->second, n + 1);
		//for (i = 0; i < n; i++) putchar(' ');

		PrintTree(p->first, n + 1);

	}
}



// Вспомогательная функция, которая показывает находится ли элемент в узле или нет
int Find(struct Node* p, int key) {
	int i;
	for (i = 0; i < p->size; i++)
		if (p->key[i] == key) return 1;
	return 0;

}



// Функция поиска
struct Node* Search(struct Node* p, int key) {
	if (!p) return NULL;

	if (Find(p, key))
		return p;
	else if (key < p->key[0])
		return Search(p->first, key);
	else if ((p->size == 2 && key < p->key[1]) || p->size == 1)
		return Search(p->second, key);
	else if (p->size == 2)
		return Search(p->third, key);
}



// Поиск минимального ключа
struct Node* SearchMin(struct Node* p) {
	if (!p) return p;
	if (!(p->first)) return p;
	else return SearchMin(p->first);
}


// Удаляем ключ key из вершины 
void RemoveFromNode(struct Node* p, int key) {
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

// Перераспределение
struct Node* Redistribute(struct Node* leaf) {
	struct Node* parent = leaf->parent;
	struct Node* first = parent->first;
	struct Node* second = parent->second;
	struct Node* third = parent->third;

	if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {

		if (first == leaf) {
			parent->first = parent->second;
			parent->second = parent->third;
			parent->third = NULL;
			InsertToNode(parent->first, parent->key[0]);
			parent->first->third = parent->first->second;
			parent->first->second = parent->first->first;

			if (leaf->first != NULL) 
				parent->first->first = leaf->first;
			else if (leaf->second != NULL) 
				parent->first->first = leaf->second;

			if (parent->first->first != NULL) 
				parent->first->first->parent = parent->first;

			RemoveFromNode(parent, parent->key[0]);

			free(first);

		}
		else if (second == leaf) {

			InsertToNode(first, parent->key[0]);
			RemoveFromNode(parent, parent->key[0]);


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

			InsertToNode(second, parent->key[1]);
			parent->third = NULL;
			RemoveFromNode(parent, parent->key[1]);

			if (leaf->first != NULL) 
				second->third = leaf->first;
			else if (leaf->second != NULL) 
				second->third = leaf->second;

			if (second->third != NULL)  
				second->third->parent = second;

			free(third);

		}

	}
	else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {

		if (third == leaf) {

			if (leaf->first != NULL) {
				leaf->second = leaf->first;
				leaf->first = NULL;
			}

			InsertToNode(leaf, parent->key[1]);

			if (second->size == 2) {
				parent->key[1] = second->key[1];
				RemoveFromNode(second, second->key[1]);
				leaf->first = second->third;
				second->third = NULL;

				if (leaf->first != NULL)
					leaf->first->parent = leaf;

			}
			else if (first->size == 2){

				parent->key[1] = second->key[0];
				leaf->first = second->second;
				second->second = second->first;

				if (leaf->first != NULL) 
					leaf->first->parent = leaf;

				second->key[0] = parent->key[0];
				parent->key[0] = first->key[1];
				RemoveFromNode(first, first->key[1]);
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

				InsertToNode(second, parent->key[1]);
				parent->key[1] = third->key[0];
				RemoveFromNode(third, third->key[0]);

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

				InsertToNode(second, parent->key[0]);
				parent->key[0] = first->key[1];
				RemoveFromNode(first, first->key[1]);

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

			InsertToNode(first, parent->key[0]);

			if (second->size == 2) {
				parent->key[0] = second->key[0];
				RemoveFromNode(second, second->key[0]);
		
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
				RemoveFromNode(third, third->key[0]);
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
		
		InsertToNode(leaf, parent->key[0]);

		if (first == leaf && second->size == 2) {
			parent->key[0] = second->key[0];
			RemoveFromNode(second, second->key[0]);

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
			RemoveFromNode(first, first->key[1]);

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



// Склеивание
struct Node* Merge(struct Node* leaf) {

	struct Node* tmp = NULL;
	struct Node* parent = leaf->parent;

	if (parent->first == leaf) {
		InsertToNode(parent->second, parent->key[0]);
		parent->second->third = parent->second->second;
		parent->second->second = parent->second->first;

		if (leaf->first != NULL) 
			parent->second->first = leaf->first;
		else if (leaf->second != NULL) 
			parent->second->first = leaf->second;

		if (parent->second->first != NULL) 
			parent->second->first->parent = parent->second;

		RemoveFromNode(parent, parent->key[0]);

		free(parent->first);
		parent->first = NULL;

	}
	else if (parent->second == leaf) {
		InsertToNode(parent->first, parent->key[0]);

		if (leaf->first != NULL) 
			parent->first->third = leaf->first;
		else if (leaf->second != NULL) 
			parent->first->third = leaf->second;

		if (parent->first->third != NULL) 
			parent->first->third->parent = parent->first;

		RemoveFromNode(parent, parent->key[0]);

		free(parent->second);
		parent->second = NULL;
	}

	if (parent->parent == NULL) {

		if (parent->first != NULL) 
			tmp = parent->first;
		else tmp = parent->second;

		tmp->parent = NULL;
		free(parent);
		return tmp;
	}

	return parent;
}



// Исправление дерева после удаления
struct Node* Fix(struct Node* leaf) {

	struct Node* parent = leaf->parent;

	// Случай 0, когда удаляем единственный ключ в дереве
	if (leaf->size == 0 && leaf->parent == NULL) { 
		free(leaf);
		return NULL;
	}

	// Случай 1, когда вершина, в которой удалили ключ, имела два ключа
	if (leaf->size != 0) { 
		if (leaf->parent) 
			return Fix(leaf->parent);
		else return leaf;
	}

	// Случай 2, когда достаточно перераспределить ключи в дереве
	if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) 
		leaf = Redistribute(leaf); 
	// Аналогично
	else if (parent->size == 2 && parent->third->size == 2) 
		leaf = Redistribute(leaf); 

	// Случай 3, когда нужно произвести склеивание и пройтись вверх по дереву как минимум на еще одну вершину
	else leaf = Merge(leaf); 

	return Fix(leaf);

}



// Удаление ключа
struct Node* Remove(struct Node* p, int key) {

	// Ищем узел, где находиться ключ key
	struct Node* item = Search(p, key);

	struct Node* min = NULL;
	int z = 0;

	/////////////////////////////////////////////
	//if (!item) return p;
	if (!item) return NULL;

	// Ищем эквивалентный ключ
	if (item->key[0] == key)
		min = SearchMin(item->second);
	else
		min = SearchMin(item->third);

	// Меняем ключи местами
	if (min) {
		//z = (key == item->key[0] ? item->key[0] : item->key[1]);

		if (key == item->key[0]) {
			z = item->key[0];
			item->key[0] = min->key[0];
			min->key[0] = z;
		}
		else {
			z = item->key[1];
			item->key[1] = min->key[0];
			min->key[0] = z;
		}

		item = min;
	}

	// Удаляем требуемый ключ
	RemoveFromNode(item, key);

	// Востановление свойства дерева
	return Fix(item);
}




//int main() {
//
//	char comand;
//	int key;
//	struct Node* root = NULL;
//
//	while (1) {
//		comand = fgetc(stdin);
//
//		if (comand == EOF || comand == '\n')
//		//if (comand == EOF)
//			break;
//
//		scanf("%i", &key);
//
//		if (comand == 'a') {
//			if (Search(root, key)) {
//				//printf("Tree already has this key\n");
//			}
//			else {
//				root = Insert(root, key);
//			}
//		}
//		else if (comand == 'r') {
//			if (!Search(root, key)) {
//				//printf("Tree don't have this key\n");
//			}
//			else {
//				//root = Insert(root, key);
//				root = Remove(root, key);
//			}
//		}
//		else if (comand == 'f') {
//			if (Search(root, key)) {
//				printf("yes\n");
//			}
//			else {
//				printf("no\n");
//			}
//		}
//
//		key = 0;
//		comand = fgetc(stdin);
//
//	}
//
	//struct Node* newNode = CreateNode(13);
	//printf("%i\n", IsLeaf(newNode));
	//printf("%i ", newNode->key[0]);
	//printf("%i ", newNode->key[1]);
	//printf("%i\n", newNode->key[2]);
	//InsertToNode(newNode, 5);
	//InsertToNode(newNode, 7);
	//Sort(newNode);
	//printf("%i ", newNode->key[0]);
	//printf("%i ", newNode->key[1]);
	//printf("%i\n", newNode->key[2]);
	//free(newNode);

	//struct Node* newNode = CreateNode(13);
	//struct Node* newNode1;
	//struct Node* newS;

	//printf("%i ", newNode->key[0]);
	//printf("%i \n", newNode->key[1]);
	//Insert(newNode, 5);
	//printf("%i ", newNode->key[0]);
	//printf("%i \n", newNode->key[1]);

	//newNode1 = Insert(newNode, 8);
	//Insert(newNode, 18);
	//newNode1 = Insert(newNode, 15);
	//printf("%i \n", newNode1->key[0]);
	//printf("%i ", newNode1->first->key[0]);
	//printf("%i ", newNode1->second->key[0]);

	//printf("%i \n", LenTree(newNode1));
	//PrintTree(newNode1, 2);
	//printf("\n\n\n");
	//newS = Search(newNode1, 13);
	//printf("%p \n", newS);
	//printf("%i \n", newS->key[0]);
	
	//newS = Search(newNode1, 16);
	//printf("%i \n", newS);
	//printf("%i ", newNode1->key[0]);
	//printf("%i ", newNode1->key[1]);

	//free(newNode);
	//free(newNode1);
	//PrintTree(root, 5);
//	return 0;
//}
