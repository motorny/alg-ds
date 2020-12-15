#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct tree_t { //структура дерева
	int a;

	struct tree_t* left;

	struct tree_t* right;

	int v; //разница высот

}tree;

 
tree* memTree(int elem) {  // Выделение памяти для узла


	tree* node = (tree*)malloc(sizeof(tree));


	if (node!=NULL) {
		node->left = NULL;
		node->right = NULL;

		node->a = elem;
		
	}

	return node;
}
void freeTree(tree* t) { //Освобождение памяти


	if (t!=NULL) {
		freeTree(t->left);
		freeTree(t->right);

		free(t);
	}
}


void print(tree* t, char* dir, int level) {
	if (t) {
		printf("lvl %d %s = %d  order = %i\n", level, dir, t->a, t->v);
		print(t->left, "left", level + 1);
		print(t->right, "right", level + 1);
	}
}


tree* Find(tree* t, int el) {


	while (t) {

		if (el > t->a) {

			t = t->right;
			continue;
		}

		if (el < t->a) {

			t = t->left;
			continue;
		}

		
			return t;
		
	}
	return NULL;
}


void Add(tree** t, int el) {


	tree* lst = (*t);



	if ((*t) == NULL) {  // если это корень

		(*t) = memTree(el);

		return;
	}


	
		if (el > lst->a) {
	
			Add(&(lst->right), el);
			
		}

		if (el < lst->a) {

			Add(&(lst->left), el);
		}


		if (el == lst->a)
			return;
	

}




void Del(tree** t, int el) {


	tree* lst = NULL;
	tree** lst2;


	if (t) {
		while (*t) {

			if (el > (*t)->a) {
				(t) = &((*t)->right);
			}

			else if (el < (*t)->a) {
				(t) = &((*t)->left);
			}


			else {

				lst = (*t);

				if (!(*t)->left && !(*t)->right) // Если нет детей
					(*t) = NULL;

				else if (!(*t)->left) // Если есть один из детей
					(*t) = (*t)->right;

				else if (!(*t)->right)
					(*t) = (*t)->left;

				else {

					lst2 = &(*t)->left;

					while ((*lst2)->right)
						lst2 = &(*lst2)->right;


					(*t)->a = (*lst2)->a;
					lst = *lst2;
					(*lst2) = (*lst2)->left;
				}

				free(lst);
			}

		}
	}
}


int hight(tree* t) { // записывает разницу высот поддеревьев

	int l, r, max;
	
	if (t == NULL)
		return 0;
	
	l = hight(t->left);
	r = hight(t->right);

	t->v = l - r;

	max = l > r ? l: r;


	return max + 1;

}


int main(void) {
    char  c = 0;
	int r = -1, i = 0;


	tree* tree = NULL;
	
	while (!feof(stdin) && 2 == scanf("%c %d %*[ \n]", &c, &r)) {
		
		i = 0;
		if (c== 'a')
			Add(&tree, r);
			
		if (c == 'f') {
			if (Find(tree, r))
				printf("yes\n");
			else
				printf("no\n");
		}


		if (c =='r') 
			Del(&tree, r);
			
		
		
	}

	freeTree(tree);
	return 0;
}