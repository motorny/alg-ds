#include "C4.h"

typedef struct knot_t {
	int con_c;
	int* con_knots;
	bool flag;
}knot_t;

typedef struct queue_t {
	int elem_c;
	int* elems;
}queue_t;

void queue_init(queue_t* que) {
	que->elem_c = 0;
	que->elems = NULL;
}

void queue_push(queue_t* que, int pushEl) {
	que->elem_c++;
	que->elems = realloc(que->elems, que->elem_c * sizeof(int));
	for (int i = que->elem_c - 1; i > 0; i--) {
		que->elems[i] = que->elems[i - 1];
	}
	que->elems[0] = pushEl;
}

int queue_pop(queue_t* que) {
	int popEl = que->elems[que->elem_c - 1];
	que->elem_c--;
	if (que->elem_c != 0)
		que->elems = realloc(que->elems, que->elem_c * sizeof(int));
	else {
		free(que->elems);
		que->elems = NULL;
	}
	return popEl;
}

void insert_con(knot_t* all_knots, int knot_change, int knot_ins) {
	int placeForKnot = -1;
	int temp = -1;
	all_knots[knot_change].con_knots = realloc(all_knots[knot_change].con_knots, (all_knots[knot_change].con_c + 1) * sizeof(int));
	for (int i = 0; i < all_knots[knot_change].con_c; i++) {
		if (all_knots[knot_change].con_knots[i] > knot_ins) {
			placeForKnot = i;
			break;
		}
	}
	if (placeForKnot != -1) {
		temp = all_knots[knot_change].con_knots[placeForKnot];
		all_knots[knot_change].con_knots[placeForKnot] = knot_ins;
		all_knots[knot_change].con_knots[all_knots[knot_change].con_c] = temp;
	}
	else {
		all_knots[knot_change].con_knots[all_knots[knot_change].con_c] = knot_ins;
	}
	all_knots[knot_change].con_c++;
}

void get_con(knot_t* all_knots) {
	int knot1 = -1, knot2 = -1, pointer = 0;
	char string[5] = "", sym = '0';
	while (sym != EOF) {
		pointer = 0;
		do {
			sym = fgetc(stdin);
			string[pointer] = sym;
			pointer++;
		} while (sym != EOF && sym != '\r' && sym != '\n' && sym != ' ');
		if (sym == '\r')
			fgetc(stdin);

		knot1 = atoi(string);
		if (sym == ' ') {
			pointer = 0;
			do {
				sym = fgetc(stdin);
				string[pointer] = sym;
				pointer++;
			} while (sym != EOF && sym != '\r' && sym != '\n');
			if (sym == '\r')
				fgetc(stdin);

			knot2 = atoi(string);
			insert_con(all_knots, knot1, knot2);
			insert_con(all_knots, knot2, knot1);
		}
	}
}

void bfs(knot_t* all_knots, queue_t* que){
	int num_go = -1;
	queue_push(que, 0);
	all_knots[0].flag = true;
	while (que->elem_c > 0) {
		num_go = queue_pop(que);
		printf("%d ", num_go);
		for (int i = 0; i < all_knots[num_go].con_c; i++) {
			if (!all_knots[all_knots[num_go].con_knots[i]].flag) {
				queue_push(que, all_knots[num_go].con_knots[i]);
				all_knots[all_knots[num_go].con_knots[i]].flag = true;
			}
		}
	}
}

/*
int main(void) {
	int knots = 0;
	char sym = '0';
	int pointer = 0;
	knot_t* all_knots = NULL;
	queue_t queue;

	char string[20] = "";
	while (sym != EOF && sym != '\r' && sym != '\n') {
		sym = fgetc(stdin);
		string[pointer] = sym;
		pointer++;
	}
	if (sym == '\r')
		fgetc(stdin);
	knots = atoi(string);

	all_knots = malloc(sizeof(knot_t) * knots);
	for (int i = 0; i < knots; i++) {
		all_knots[i].con_knots = NULL;
		all_knots[i].con_c = 0;
		all_knots[i].flag = false;
	}

	get_con(all_knots);
	queue_init(&queue);
	bfs(all_knots, &queue);

	for (int i = 0; i < knots; i++) {
		free(all_knots[i].con_knots);
	}
	free(all_knots);

	return 0;
}*/