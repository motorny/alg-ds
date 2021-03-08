#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define plus 1024
#pragma warning(disable: 4996)

typedef struct vertex {
	int cle;
	int prev;
	struct vertex* left;
	struct vertex* right;
}vertex;

char* scanString() {
	char* string = NULL;
	char* p = NULL;
	int k = 0;
	int size = plus;
	string = (char*)malloc(plus * sizeof(char));
	if (!string)
		return NULL;
	while ((string[k] = fgetc(stdin)) != EOF) {
		k++;
		if (k >= size) {
			p = (char)realloc(string, (size + plus) * sizeof(char));
			size += plus;
		}
		if (p)
			string = p;
		else
			return NULL;

	}
	string[k] = 0;
	return string;
}
vertex* combine(vertex* g, vertex* d) {
	if (!g || !d)
		return g ? g : d;
	if (g->prev > d->prev) {
		g->right = combine(g->right, d);
		return g;
	}
	else {
		g->left = combine(g, d->left);
		return d;
	}
}
void parted(vertex* tr, int cle, vertex** g, vertex** d) {
	if (!tr) {
		(*g) = (*d) = NULL;
		return;
	}
	if (tr-> cle < cle) {
		parted(tr->right, cle, &(tr->right), d);
		(*g) = tr;
	}
	else {
		parted(tr->left, cle, g, &(tr->left));
		(*d) = tr;
	}
}

vertex* getFork(int cle) {
	vertex* tr = (vertex*)malloc(sizeof(vertex));
	if (tr) {
		tr->left = tr->right = NULL;
		tr->cle = cle;
		tr->prev = rand();
	}
	return tr;
}
void sum(vertex** tr, int cle) {
	if (!(*tr)) {
		(*tr) = getFork(cle);
		return;
	}
	vertex* smaller = NULL, * larger = NULL;
	parted(*tr, cle, &smaller, &larger);
	(*tr) = combine(combine(smaller, getFork(cle)), larger);
}

int uncover(vertex* tr, int cle) {
	int decs = 0;
	vertex* smaller = NULL, * larger = NULL, * upTo = NULL;
	parted(tr, cle, &smaller, &larger);
	parted(larger, cle + 1, &upTo, &larger);
	if (upTo)
		decs = 1;
	tr = combine(combine(smaller, upTo), larger);
	return decs;
}

int eraseItm(vertex** tr, int cle) {
	int decs = 0;
	vertex* smaller = NULL, * larger = NULL, * upTo = NULL;
	parted(*tr, cle, &smaller, &larger);
	parted(larger, cle + 1, &upTo, &larger);
	if (upTo)
		decs = 1;
	free(upTo);
	(*tr) = combine(smaller, larger);
	return decs;
}

void displayBinTree(vertex* tr, char* dr, int degree) {
	if (tr) {
		printf("lvl %d %s = %d  prev = %i\n", degree, dr, tr->cle, tr->prev);
		displayBinTree(tr->left, "left", degree + 1);
		displayBinTree(tr->right, "right", degree + 1);
	}
}

void wreck(vertex* tr) {
	if (tr) {
		wreck(tr->left);
		wreck(tr->right);
		free(tr);
	}
}


int main()
{
	char* string = scanString(), * save = NULL;
	int cle;
	char instr;
	vertex* tr = NULL;
	save = strtok(string, "\n");
	while (save) {
		if (sscanf(save, "%c%i", &instr, &cle));
		switch (instr)
		{
		case 'a':
			sum(&tr, cle);
			break;
		case 'f':
			if (uncover(tr, cle))
				printf("yes\n");
			else
				printf("no\n");
			break;
		case 'r':
			eraseItm(&tr, cle);
			break;

		}
		save = strtok(NULL, "\n");
	}
	free(string);
	wreck(tr);

	return 0;
}