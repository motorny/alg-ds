#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define MORE_PINS 2
#define N 3

typedef struct tree_t {
	int label;
	int pins;
	int rate[2 * N - 1];
	struct tree_t* offsprings[2 * N];
}tree_t;


tree_t* MakeTree() {
	tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
	if (tree == NULL)
		return NULL;

	tree->label = 1;
	tree->pins = 0;

	for (int i = 0; i < 2 * N; i++)
		tree->offsprings[i] = NULL;

	return tree;
}



void Bust(tree_t* tree, int spot) {
	tree_t* dtree = MakeTree();
	tree_t* offspringson = tree->offsprings[spot];

	dtree->label = offspringson->label;
	dtree->pins = N - 1;

	for (int i = 0; i < N - 1; i++)
		dtree->rate[i] = offspringson->rate[i + N];
	if (offspringson->label == 0) {
		for (int i = 0; i < N; i++) {
			dtree->offsprings[i] = offspringson->offsprings[i + N];
			offspringson->offsprings[i + N] = NULL;
		}
	}

	offspringson->pins = N - 1;
	if (tree->offsprings[spot + 1] != NULL) {
		int iter = spot + 1;
		while (tree->offsprings[iter] != NULL)
			iter++;
		for (iter; iter > spot + 1; iter--) {
			tree->rate[iter - 1] = tree->rate[iter - 2];
			tree->offsprings[iter] = tree->offsprings[iter - 1];
		}
	}

	tree->pins = tree->pins + 1;
	tree->offsprings[spot + 1] = dtree;
	tree->rate[spot] = offspringson->rate[N - 1];

}




void FitSpot(tree_t* tree, int rate) {
	int spot = tree->pins - 1;
	if (tree->label == 1) {
		while (spot >= 0 && rate < tree->rate[spot]) {
			tree->rate[spot + 1] = tree->rate[spot];
			spot--;
		}
		tree->pins++;
		tree->rate[spot + 1] = rate;
	}
	else {
		while (spot >= 0 && rate < tree->rate[spot])
			spot--;
		if (tree->offsprings[spot + 1]->pins == 2 * N - 1) {
			Bust(tree, spot + 1);
			if (tree->rate[spot + 1] < rate)
				spot = spot + 1;
		}
		spot = spot + 1;
		FitSpot(tree->offsprings[spot], rate);
	}
}

int Explore(tree_t* tree, int rate) {
	if (tree == NULL)
		return 0;
	else {
		int iter = 0;
		while (iter < tree->pins && rate > tree->rate[iter]) {
			iter++;
		}
		if (iter < tree->pins && rate == tree->rate[iter])
			return 1;
		else if (tree->label == 1)
			return 0;
		else return Explore(tree->offsprings[iter], rate);
	}
}



void Fit(tree_t** tree, int rate) {
	if (!(*tree)) {
		(*tree) = MakeTree();
		(*tree)->rate[0] = rate;
		(*tree)->pins = 1;
		return;
	}
	else {
		if (Explore((*tree), rate) == 1)
			return;
		else {
			if ((*tree)->pins < 2 * N - 1) {
				FitSpot((*tree), rate);
			}
			else {
				tree_t* dtree = MakeTree();
				tree_t* temp = (*tree);
				(*tree) = dtree;
				dtree->label = 0;
				dtree->pins = 0;
				dtree->offsprings[0] = temp;
				Bust(dtree, 0);
				FitSpot(dtree, rate);
			}
		}
	}
}


int Withdraw(tree_t* tree, int rate) {
	if (!tree)
		return 0;

	int requirmts = (N - 1) / 2;

	int treepins = tree->pins;
	int* treerate = tree->rate;
	tree_t** treeoffsprings = tree->offsprings;

	int spot = 0;
	while (spot < treepins && rate > treerate[spot])
		spot++;

	if (!treeoffsprings[0]) {
		if (rate < treerate[spot] || spot == treepins)
			return 0;
		for (int i = spot + 1; i < treepins; i++) {
			treerate[i - 1] = treerate[i];
			treeoffsprings[i] = treeoffsprings[i + 1];
		}
		tree->pins--;
		if (tree->pins >= requirmts)
			return 1;
		else
			return MORE_PINS;
	}

	tree_t* temp1;
	int pins1;
	tree_t* temp2;

	if (spot < treepins && rate == treerate[spot]) {
		temp1 = treeoffsprings[rate];
		for (;;) {
			pins1 = temp1->pins;
			temp2 = temp1->offsprings[pins1];
			if (!temp2)
				break;
			temp1 = temp2;
		}
		treerate[spot] = temp1->rate[pins1 - 1];
		temp1->rate[pins1 - 1] = rate;
	}
	int rank = Withdraw(treeoffsprings[spot], rate);
	if (rank != MORE_PINS)
		return rank;

	tree_t* l;
	tree_t* r;

	if (spot > 0 && treeoffsprings[spot - 1]->pins > requirmts) {
		l = treeoffsprings[spot - 1];
		r = treeoffsprings[spot];
		r->offsprings[r->pins + 1] = r->offsprings[r->pins];
		for (int i = r->pins; i > 0; i--) {
			r->rate[i] = r->rate[i - 1];
			r->offsprings[i] = r->offsprings[i - 1];
		}
		r->pins++;
		r->rate[0] = treerate[spot - 1];
		r->offsprings[0] = l->offsprings[l->pins];
		treerate[spot - 1] = l->rate[--l->pins];
		return 1;
	}
	
	if (spot < treepins && treeoffsprings[spot + 1]->pins > requirmts) {
		l = treeoffsprings[spot];
		r = treeoffsprings[spot + 1];
		l->rate[l->pins] = treerate[spot];
		l->offsprings[l->pins + 1] = r->offsprings[0];
		treerate[spot] = r->rate[0];
		l->pins++;
		r->pins--;
		for (int i = 0; i < r->pins; i++) {
			r->rate[i] = r->rate[i + 1];
			r->offsprings[i] = r->offsprings[i + 1];
		}
		r->offsprings[r->pins] = r->offsprings[r->pins + 1];
		return 1;
	}

	if (spot == treepins) {
		l = treeoffsprings[spot - 1];
		r = treeoffsprings[spot];
		l->rate[l->pins] = treerate[spot - 1];
	}
	else {
		l = treeoffsprings[spot];
		r = treeoffsprings[spot + 1];
		l->rate[l->pins] = treerate[spot];
	}
	l->offsprings[l->pins + 1] = r->offsprings[0];
	for (int i = 0; i < r->pins; i++) {
		l->rate[l->pins + i + 1] = r->rate[i];
		l->offsprings[l->pins + i + 2] = r->offsprings[i + 1];
	}
	l->pins = l->pins + r->pins + 1;
	free(r);
	for (int i = spot + 1; i < treepins; i++) {
		treerate[i - 1] = treerate[i];
		treeoffsprings[i] = treeoffsprings[i + 1];
	}
	tree->pins--;
	if (tree->pins >= requirmts)
		return 1;
	else return MORE_PINS;
}



void EraseElm(tree_t* tree, int rate) {
	if (tree == NULL)
		return;
	int rank = Withdraw(tree, rate);
	if (rank == MORE_PINS) {
		tree_t* releasefork = tree;
		tree = tree->offsprings[0];
		free(releasefork);
	}
}

void Display(tree_t* tree, int lvl) {
	int i;
	if (tree == NULL)
		return;
	for (i = 0; i <= tree->pins - 1; i++) {
		Display(tree->offsprings[i], lvl + 1);
		for (int j = 0; j <= lvl; j++)
			printf("   ");
		printf("%d\n", tree->rate[i]);
	}
	Display(tree->offsprings[i], lvl + 1);
}

void EraseTree(tree_t* tree) {
	if (tree == NULL)
		return;
	if (tree->label == 0) {
		for (int i = 0; i <= tree->pins; i++) {
			EraseTree(tree->offsprings[i]);
		}
	}
	free(tree);
}




int main() {
	char cmd;
	int rate;
	tree_t* tree = NULL;

	cmd = (char)getchar();
	while (cmd != EOF) {
		scanf("%d", &rate);
		switch (cmd) {
		case 'a':
		{
			Fit(&tree, rate);
			break;
		}
		case 'f':
		{
			if (Explore(tree, rate) == 0)
				puts("no");
			else if (Explore(tree, rate) == 1)
				puts("yes");
			break;
		}
		case 'r':
		{
			EraseElm(tree, rate);
			break;
		}
		default:
			break;
		}
		cmd = (char)getchar();
		if (cmd == '\r' || cmd == '\n')
			cmd = (char)getchar();
	}

	EraseTree(tree);
	return 0;
}