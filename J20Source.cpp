#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#pragma warning (disable:4996)

typedef struct unit_t {
	int rate;
	struct unit_t* forward;
} unit_t;

typedef struct hash_arr_t {
	int dim;
	unit_t** web;
}hash_arr_t;

int Hash(hash_arr_t* arr, int val) {
	return abs(val) % arr->dim;
}

hash_arr_t* Make(int dim) {
	hash_arr_t* arr = (hash_arr_t*)malloc(sizeof(hash_arr_t));
	if (!arr) {
		return NULL;
	}
	arr->dim = dim;
	arr->web = (unit_t**)malloc(sizeof(unit_t*) * dim);
	if (!arr->web) {
		free(arr);
		return NULL;
	}
	for (int i = 0; i != dim; i++) {
		arr->web[i] = NULL;
	}
	return arr;
}

void Smash(hash_arr_t* arr) {
	if (!arr)
		return;
	for (int i = 0; i != arr->dim; i++) {
		unit_t* pitch = arr->web[i];
		while (pitch) {
			unit_t* bf = pitch;
			pitch = pitch->forward;
			free(bf);
		}
	}
	free(arr->web);
	free(arr);
}

int MakeFork(unit_t** fork) {
	*fork = (unit_t*)malloc(sizeof(unit_t));
	if (!*fork) {
		return 0;
	}
	(*fork)->forward = NULL;
	(*fork)->rate = 0;
	return 1;
}

int Discov(hash_arr_t* arr, int val) {
	int mark = Hash(arr, val);
	unit_t* bf = arr->web[mark];

	while (bf) {
		if (bf->rate == val)
			return 1;
		bf = bf->forward;
	}
	return 0;
}

void Sum(hash_arr_t* arr, int val) {
	if (Discov(arr, val))
		return;

	int mark = Hash(arr, val);
	unit_t** unit = &arr->web[mark];
	unit_t** forwardunit = unit;

	if (!(*forwardunit)) {
		if (!MakeFork(forwardunit))
			return;
		(*forwardunit)->rate = val;
	}
	else {
		while (*forwardunit) {
			unit = forwardunit;
			forwardunit = &(*forwardunit)->forward;
		}
		if (!MakeFork(forwardunit))
			return;
		(*forwardunit)->rate = val;
		(*unit)->forward = *forwardunit;
	}
}
void Withdraw(hash_arr_t* arr, int val) {
	if (!Discov(arr, val))
		return;

	int mark = Hash(arr, val);
	unit_t* unit = arr->web[mark];
	unit_t* priorunit = unit;

	if (unit->rate == val) {
		arr->web[mark] = unit->forward;
		free(unit);
	}
	else {
		while (unit) {
			if (unit->rate == val) {
				priorunit->forward = unit->forward;
				free(unit);
				return;
			}
			priorunit = unit;
			unit = unit->forward;
		}
	}
}
void Must(hash_arr_t** arr) {
	char sym;
	int val;

	while ((sym = getchar()) != EOF) {
		scanf("%d", &val);
		if (sym == 'a')
			Sum(*arr, val);

		else if (sym == 'r')
			Withdraw(*arr, val);

		else if (sym == 'f') {
			if (Discov(*arr, val))
				printf("yes\n");

			else
				printf("no\n");

		}
		else
			return;
		getchar();
	}
}

int main() {
	int dim = 10000;
	hash_arr_t* arr = Make(dim);
	Must(&arr);
	return 0;
}